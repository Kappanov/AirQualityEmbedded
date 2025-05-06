#include <module/NetworkModule.h>
#include <module/AirQualityModule.h>

#include <sensors/DHTSensor.h>
#include <sensors/MQ135Sensor.h>
#include <sensors/MQ5Sensor.h>
#include <sensors/MQ7Sensor.h>

#define WIFI_SSID "Nabat"
#define WIFI_PASSWORD "Nabat1960"

#define MUX_OUT 2  // A0
#define MUX_IN1 20 // D1
#define MUX_IN2 19 // D2

#define DHT_PIN 5			// D5
#define MQ135_PIN MUX_OUT	// A0
#define MQ5_PIN MUX_OUT		// A0
#define MQ7_PIN MUX_OUT		// A0
#define MQ7_INTERRUPT_PIN 4 // D0

NetworkModule *netModule;
AirQualityModule *airQualityModule;

void IRAM_ATTR onActivate();
void IRAM_ATTR onPassive();
void IRAM_ATTR sendAirQuality();

void setup()
{
	Serial.begin(115200);
	Serial.println("Start setup");
	netModule = new NetworkModule(WIFI_SSID, WIFI_PASSWORD);

	auto dht = new DHTSensor(DHT_PIN);
	auto mq135 = new MQ135Sensor(MQ135_PIN);
	auto mq5 = new MQ5Sensor(MQ5_PIN);
	auto mq7 = new MQ7Sensor(MQ7_PIN, MQ7_INTERRUPT_PIN);

	airQualityModule = new AirQualityModule(dht, mq135, mq5, mq7, MUX_IN1, MUX_IN2);

	bool isHubConnected = netModule->checkHubConnection();
	Serial.printf("Is hub connected: %s\n", isHubConnected ? "true" : "false");

	if (isHubConnected)
	{
		netModule->onRequest("/active", onActivate);
		netModule->onRequest("/passive", onPassive);
	}

	airQualityModule->onRisingEdge(sendAirQuality);
	airQualityModule->onSendingData(sendAirQuality);
	Serial.println("End setup");
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

void IRAM_ATTR onActivate()
{
	airQualityModule->changeStatus(DeviceStatus::ACTIVE);
}

void IRAM_ATTR onPassive()
{
	airQualityModule->changeStatus(DeviceStatus::PASSIVE);
}

void IRAM_ATTR sendAirQuality()
{
	auto data = airQualityModule->getAirQuality();
	netModule->sendAirQualityData(data);
}