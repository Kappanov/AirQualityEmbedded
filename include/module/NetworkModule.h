#ifndef NETWORK_MODULE_H
#define NETWORK_MODULE_H

#include <enum/Hubs.h>
#include <data/AirQuality.h>
#include <module/AirQualityModule.h>

class NetworkModule {
private:
	bool connectToHub(const Hub hub);
	bool disconnectFromHub(const Hub hub);
	int connectToAllHubs();

public:
	NetworkModule(const char* SSID, const char* password);
	

	bool checkWifiConnection();
	bool checkHubConnection(const Hub Hub);
	void sendAirQualityData(const AirQuality airQualityData);

	void onRequest(const char* request, Action callback);

};

#endif