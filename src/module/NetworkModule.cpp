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

	connectToAllHubs();
}

NetworkModule::~NetworkModule()
{
	disconnectFromAllHubs();
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

DeviceStatus NetworkModule::getDeviceStatus()
{
	if (checkHubConnection(Hub::MAIN_HUB) && checkHubConnection(Hub::SCANNER_HUB))
	{
		return DeviceStatus::ACTIVE;
	}
	else if (checkHubConnection(Hub::MAIN_HUB))
	{
		return DeviceStatus::PASSIVE;
	}
	else
	{
		return DeviceStatus::POWEROFF;
	}
}

HubList NetworkModule::getConnectedHubs() const
{
	HubList list;
	std::copy(this->connectedHubs.hubs.begin(), this->connectedHubs.hubs.begin() + this->connectedHubs.count, list.hubs.begin());
	list.count = this->connectedHubs.count;
	return list;
}

bool NetworkModule::checkHubConnection(Hub hub)
{
	return this->connectedHubs.hubs[hub].isConnected();
}

void NetworkModule::sendAirQualityData(AirQuality airQuality)
{
	if (!checkWifiConnection())
	{
		Serial.println("WiFi not connected. Cannot send data.");
		return;
	}
	HTTPClient http;
	http.begin(POST_AIR_QUALITY_REQUEST);
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

void NetworkModule::onRequest(const Hub hub, const char *request, const Action callback)
{
	this->connectedHubs.hubs[hub].onEvent([this, callback, request](WStype_t type, uint8_t *payload, size_t length)
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

bool NetworkModule::connectToHub(const Hub hub)
{
	if (!checkWifiConnection())
	{
		Serial.println("WiFi not connected. Cannot connect to hub.");
		return false;
	}

	this->connectedHubs.hubs[hub].begin(HOST, PORT, HUB_PATHS[hub]);
	this->connectedHubs.hubs[hub].onEvent([this](WStype_t type, uint8_t *payload, size_t length)
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

	this->connectedHubs.hubs[hub].setReconnectInterval(5000);
	this->connectedHubs.hubs[hub].loop();

	return true;
}

bool NetworkModule::disconnectFromHub(const Hub hub)
{
	this->connectedHubs.hubs[hub].disconnect();
	Serial.println("Disconnected from WebSocket hub.");
	return true;
}

int NetworkModule::connectToAllHubs()
{
	for (int i = 0; i < this->connectedHubs.count; ++i)
	{
		connectToHub(static_cast<Hub>(i));
	}
	return 0;
}

int NetworkModule::disconnectFromAllHubs()
{
	for (int i = 0; i < this->connectedHubs.count; ++i)
	{
		disconnectFromHub(static_cast<Hub>(i));
	}
	return 0;
}

void NetworkModule::changeToActiveMode()
{
	if (checkHubConnection(Hub::SCANNER_HUB))
		return;

	connectToHub(Hub::SCANNER_HUB);
}

void NetworkModule::changeToPassiveMode()
{
	if (!checkHubConnection(Hub::SCANNER_HUB))
		return;

	disconnectFromHub(Hub::SCANNER_HUB);
}