#ifndef NETWORK_MODULE_H
#define NETWORK_MODULE_H

#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <ESP8266HTTPClient.h>
#include <data/AirQuality.h>
#include <enum/DeviceStatus.h>
#include <data/Action.h>

#define HOST "192.168.0.25" // Замените на IP сервера
#define PORT 5000
#define POST_AIR_QUALITY_REQUEST "http://192.168.0.25:5000/api/AirQuality"

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
	void loop();
};

#endif