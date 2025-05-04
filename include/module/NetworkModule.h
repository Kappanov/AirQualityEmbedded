#ifndef NETWORK_MODULE_H
#define NETWORK_MODULE_H

#include <enum/Hubs.h>
#include <data/AirQuality.h>
#include <module/AirQualityModule.h>
#include <enum/DeviceStatus.h>
#include <data/EventActionList.h>

class NetworkModule {
private:
	bool isWifiConnected;
	Hub* connectedHubs;
	DeviceStatus status;
	EventActionList eventActions;

	bool connectToHub(const Hub hub);
	bool disconnectFromHub(const Hub hub);
	int connectToAllHubs();
	int disconnectFromAllHubs();

public:
	NetworkModule(const char* SSID, const char* password);
	~NetworkModule();

	bool connectToWifi();
	bool start();
	DeviceStatus getDeviceStatus();
	bool checkWifiConnection();
	Hub* getConnectedHubs();
	bool checkHubConnection(const Hub Hub);
	void sendAirQualityData(const AirQuality airQualityData);

	void onRequest(const char* request, const Action callback);
};

#endif