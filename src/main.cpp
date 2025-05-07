#include <module/NetworkModule.h>
#include <module/AirQualityModule.h>
#include <sensors/DHTSensor.h>
#include <sensors/MQ135Sensor.h>
#include <sensors/MQ5Sensor.h>
#include <sensors/MQ7Sensor.h>

#define WIFI_SSID "Kv 81"
#define WIFI_PASSWORD "ernarastro01"

#define MUX_OUT A0			 // Аналоговый пин A0
#define MUX_IN1 D1			 // GPIO 5
#define MUX_IN2 D2			 // GPIO 4
#define MUX_IN3 D3			 // GPIO 0 (добавлен для 8 каналов)
#define DHT_PIN D7			 // GPIO 14
#define MQ7_INTERRUPT_PIN D0 // GPIO 16

NetworkModule *netModule;
AirQualityModule *airQualityModule;
DHT __dht(DHT_PIN, DHT11);

void IRAM_ATTR onActivate();
void IRAM_ATTR onPassive();
void IRAM_ATTR sendAirQuality();

void setup()
{
	Serial.begin(115200);
	Serial.println("Start setup");

	netModule = new NetworkModule(WIFI_SSID, WIFI_PASSWORD);

	auto dht = new DHTSensor(&__dht);
	auto mq135 = new MQ135Sensor(MUX_OUT);
	auto mq5 = new MQ5Sensor(MUX_OUT);
	auto mq7 = new MQ7Sensor(MUX_OUT, MQ7_INTERRUPT_PIN);

	airQualityModule = new AirQualityModule(dht, mq135, mq5, mq7, MUX_IN1, MUX_IN2, MUX_IN3);

	bool isHubConnected = netModule->checkHubConnection();
	Serial.printf("Is hub connected: %s\n", isHubConnected ? "true" : "false");

	if (isHubConnected)
	{
		netModule->onRequest("active", onActivate);
		netModule->onRequest("passive", onPassive);
	}

	airQualityModule->onRisingEdge(sendAirQuality);
	airQualityModule->onSendingData(sendAirQuality);
	Serial.println("End setup");
}

void loop()
{
	netModule->loop(); // Обработка WebSocket
	airQualityModule->loop();
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