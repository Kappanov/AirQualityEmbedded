#ifndef NETWORK_MODULE_H
#define NETWORK_MODULE_H

#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <ESP8266HTTPClient.h>

#include <enum/Hubs.h>
#include <data/AirQuality.h>
#include <module/AirQualityModule.h>
#include <enum/DeviceStatus.h>
#include <data/EventActionList.h>
#include <data/HubList.h>

#define HOST "localhost"
#define PORT 5000

#define POST_AIR_QUALITY_REQUEST "http://localhost:5000/api/AirQuality"

constexpr const char *HUB_PATHS[] = {"main-hub", "sensor-hub"};

class NetworkModule
{
private:
	const char *SSID;
	const char *password;
	bool isWifiConnected;
	HubList connectedHubs;
	DeviceStatus status;
	EventActionList eventActions;

	bool connectToHub(const Hub hub);
	bool disconnectFromHub(const Hub hub);
	int connectToAllHubs();
	int disconnectFromAllHubs();

public:
	NetworkModule(const char *SSID, const char *password);
	~NetworkModule();

	bool connectToWifi();
	DeviceStatus getDeviceStatus();
	bool checkWifiConnection();
	HubList getConnectedHubs() const;
	bool checkHubConnection(const Hub Hub);
	void sendAirQualityData(const AirQuality airQualityData);

	void onRequest(const Hub hub, const char *request, const Action callback);
};

#endif