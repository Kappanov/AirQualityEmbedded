#ifndef NETWORK_MODULE_H
#define NETWORK_MODULE_H

#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <ESP8266HTTPClient.h>

#include <data/AirQuality.h>
#include <module/AirQualityModule.h>
#include <enum/DeviceStatus.h>

#define HOST "localhost"
#define PORT 5000

#define POST_AIR_QUALITY_REQUEST "http://localhost:5000/api/AirQuality"

class NetworkModule
{
private:
	const char *SSID;
	const char *password;
	bool isWifiConnected;
	DeviceStatus status;
	WebSocketsClient hub;

	bool connectToHub();
	bool disconnectFromHub();
	bool connectToWifi();

public:
	NetworkModule(const char *SSID, const char *password);
	~NetworkModule();

	bool checkWifiConnection();
	bool checkHubConnection();
	void sendAirQualityData(const AirQuality airQualityData);
	void onRequest(const char *request, const Action callback);
};

#endif