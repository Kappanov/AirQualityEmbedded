#include <module/NetworkModule.h>

NetworkModule::NetworkModule(const char *SSID, const char *password)
	: SSID(SSID), password(password), isWifiConnected(false), status(DeviceStatus::POWEROFF)
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
		Serial.print(".");
		attempts++;
	}
	isWifiConnected = WiFi.status() == WL_CONNECTED;
	if (isWifiConnected)
	{
		Serial.println("\nWiFi connected, IP: " + WiFi.localIP().toString());
	}
	return isWifiConnected;
}

bool NetworkModule::checkWifiConnection()
{
	isWifiConnected = WiFi.status() == WL_CONNECTED;
	return isWifiConnected;
}

bool NetworkModule::checkHubConnection()
{
	return hub.isConnected();
}

void NetworkModule::sendAirQualityData(const AirQuality airQualityData)
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

	String payload = airQualityData.toJson();
	Serial.println("Sending payload: " + payload);
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
	hub.onEvent([request, callback](WStype_t type, uint8_t *payload, size_t length)
				{
    switch (type) {
      case WStype_TEXT:
        if (strcmp((const char *)payload, request) == 0) {
          callback();
        }
        break;
      case WStype_DISCONNECTED:
        Serial.println("WebSocket disconnected");
        break;
      case WStype_CONNECTED:
        Serial.println("WebSocket connected");
        break;
    } });
}

bool NetworkModule::connectToHub()
{
	Serial.println("Trying to connect to hub");

	if (!checkWifiConnection())
	{
		Serial.println("WiFi not connected. Cannot connect to hub.");
		return false;
	}

	hub.begin(HOST, PORT, "/controlHub"); // SignalR хаб
	hub.setReconnectInterval(5000);

	unsigned long startTime = millis();
	const unsigned long timeout = 10000; // 10 секунд
	while (!hub.isConnected() && (millis() - startTime < timeout))
	{
		hub.loop();
		delay(100);
	}

	if (hub.isConnected())
	{
		Serial.println("Successfully connected to hub");
		return true;
	}
	else
	{
		Serial.println("Connection to hub timed out!");
		return false;
	}
}

bool NetworkModule::disconnectFromHub()
{
	hub.disconnect();
	Serial.println("Disconnected from WebSocket hub.");
	return true;
}

void NetworkModule::loop()
{
	hub.loop();
	if (!isWifiConnected && checkWifiConnection())
	{
		connectToHub();
	}
}