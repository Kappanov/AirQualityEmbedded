#include <module/NetworkModule.h>
#include <module/AirQualityModule.h>

#include <sensors/DHTSensor.h>
#include <sensors/MQ135Sensor.h>
#include <sensors/MQ5Sensor.h>
#include <sensors/MQ7Sensor.h>

#define WIFI_SSID "Nabat"
#define WIFI_PASSWORD "Nabat1960"

#define DHT_PIN 5	// D5
#define MQ135_PIN 2 // A0
#define MQ5_PIN 2	// A0
#define MQ7_PIN 2	// A0
#define MUX_OUT 2	// A0
#define MUX_IN1 20	// D1
#define MUX_IN2 19	// D2

NetworkModule *netModule;
AirQualityModule *airQualityModule;

void onActivate();
void onPassive();

void setup()
{
	netModule = new NetworkModule(WIFI_SSID, WIFI_PASSWORD);

	auto dht = new DHTSensor(DHT_PIN);
	auto mq135 = new MQ135Sensor(MQ135_PIN);
	auto mq5 = new MQ5Sensor(MQ5_PIN);
	auto mq7 = new MQ7Sensor(MQ7_PIN);

	airQualityModule = new AirQualityModule(dht, mq135, mq5, mq7, MUX_IN1, MUX_IN2);

	bool isMainHubConnected = netModule->checkHubConnection(Hub::MAIN_HUB);
	bool isSensorHubConnected = netModule->checkHubConnection(Hub::SCANNER_HUB);

	if (isMainHubConnected)
	{
		netModule->onRequest(Hub::MAIN_HUB, "/active", onActivate);
		netModule->onRequest(Hub::MAIN_HUB, "/passive", onPassive);
	}

	if (isSensorHubConnected)
	{
		netModule->onRequest(Hub::SCANNER_HUB, "/", sendAirQuality);
	}

	airQualityModule->onRisingEdge(sendAirQuality);
}

void loop()
{
}

int main()
{
	init();
	setup();

	while (true)
	{
		loop();
		yield();
	}

	return 0;
}

void onActivate()
{
	netModule->changeToActiveMode();
}

void onPassive()
{
	netModule->changeToPassiveMode();
}

void sendAirQuality()
{
	auto data = airQualityModule->getAirQuality();
	netModule->sendAirQualityData(data);
}