#include <module/NetworkModule.h>

NetworkModule::NetworkModule(const char *SSID, const char *password)
	: SSID(SSID), password(password)
{
	Serial.println("NetworkModule created");
	if (!connectToWifi())
	{
		Serial.println("Failed to connect Wi-Fi");
		return;
	}
	Serial.println("WiFi success connected");
	if (connectToHub())
	{
		Serial.println("Successfully connected to hub.");
	}
	else
	{
		Serial.println("Failed to connect to hub.");
		status = DeviceStatus::POWEROFF;
	}
}

NetworkModule::~NetworkModule()
{
	disconnectFromHub();
	Serial.println("NetworkModule deleted");
}

bool NetworkModule::connectToWifi()
{
	WiFi.begin(SSID, password);
	int attempts = 0;
	while (WiFi.status() != WL_CONNECTED && attempts < 20)
	{
		delay(500);
		attempts++;
	}
	const bool isConnected = WiFi.status() == WL_CONNECTED;
	this->isWifiConnected = isConnected;
	return isConnected;
}

bool NetworkModule::checkWifiConnection()
{
	const bool isConnected = WiFi.status() == WL_CONNECTED;
	this->isWifiConnected = isConnected;
	return isConnected;
}

bool NetworkModule::checkHubConnection()
{
	return hub.isConnected();
}

void NetworkModule::sendAirQualityData(AirQuality airQuality)
{
	if (!checkWifiConnection())
	{
		Serial.println("WiFi not connected. Cannot send data.");
		return;
	}
	HTTPClient http;
	WiFiClient wifiClient;
	http.begin(wifiClient, POST_AIR_QUALITY_REQUEST);
	http.addHeader("Content-Type", "application/json");

	String payload = airQuality.toJson();
	int httpResponseCode = http.POST(payload);

	if (httpResponseCode > 0)
	{
		Serial.printf("HTTP Response code: %d\n", httpResponseCode);
	}
	else
	{
		Serial.printf("Error in sending POST: %s\n", http.errorToString(httpResponseCode).c_str());
	}

	http.end();
}

void NetworkModule::onRequest(const char *request, const Action callback)
{
	hub.onEvent([this, callback, request](WStype_t type, uint8_t *payload, size_t length)
				{
		switch (type) {
		case WStype_TEXT:
			if (strcmp((const char *)payload, request) == 0) {
				callback();
			}
			break;
		default:
			break;
		} });
}

bool NetworkModule::connectToHub()
{
	Serial.println("Try connect to hub");

	if (!checkWifiConnection())
	{
		Serial.println("WiFi not connected. Cannot connect to hub.");
		return false;
	}

	hub.begin(HOST, PORT, "/");
	hub.onEvent([this](WStype_t type, uint8_t *payload, size_t length)
				{
        switch (type) {
            case WStype_DISCONNECTED:
                Serial.println("WebSocket disconnected.");
                break;
            case WStype_CONNECTED:
                Serial.println("WebSocket connected.");
                break;
            case WStype_TEXT:
                Serial.printf("WebSocket message: %s\n", payload);
                break;
            default:
                break;
        } });

	// 3. Ожидание подключения с таймаутом
	const unsigned long timeout = 10000; // 10 секунд
	const unsigned long startTime = millis();

	while (!hub.isConnected())
	{
		hub.loop();

		if (millis() - startTime > timeout)
		{
			Serial.println("Connection to hub timed out!");
			return false;
		}

		delay(100);
	}

	// 4. Установка интервала переподключения
	hub.setReconnectInterval(5000);

	Serial.println("Successfully connected to hub");
	return true;
}

bool NetworkModule::disconnectFromHub()
{
	hub.disconnect();
	Serial.println("Disconnected from WebSocket hub.");
	return true;
}
