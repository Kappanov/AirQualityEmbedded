#include <Arduino.h>

#include <module/AirQualityModule.h>
#include <ctime>

AirQualityModule::AirQualityModule(
	DHTSensor *dhtSensor,
	MQ135Sensor *mq135sensor,
	MQ5Sensor *mq5sensor,
	MQ7Sensor *mq7sensor,
	uint8_t muxIn1, uint8_t muxIn2)
	: dhtSensor(dhtSensor), mq135sensor(mq135sensor), mq5sensor(mq5sensor), mq7sensor(mq7sensor), muxIn1(muxIn1), muxIn2(muxIn2)
{
	pinMode(muxIn1, OUTPUT);
	pinMode(muxIn2, OUTPUT);
}

AirQuality AirQualityModule::getAirQuality()
{
	AirQuality airQuality;

	changeMuxChanel(0);
	auto mq5data = mq5sensor->readSensor();

	changeMuxChanel(1);
	airQuality.coPpm = mq7sensor->readSensor();

	changeMuxChanel(2);
	auto mq135data = mq135sensor->readSensor();

	auto dhtData = dhtSensor->readSensor();
	airQuality.benzenePpm = mq135data.benzene;
	airQuality.co2Ppm = mq135data.co2;
	airQuality.nh3Ppm = mq135data.nh3;
	airQuality.lpgPpm = mq5data.lpg;
	airQuality.temperature = dhtData.temperature;
	airQuality.humidity = dhtData.humidity;
	airQuality.timestamp = time(nullptr);

	return airQuality;
}

void AirQualityModule::onRisingEdge(Action callbackOnRisingEdge)
{
	mq7sensor->onRisingEdge(callbackOnRisingEdge);
}

AirQualityModule::~AirQualityModule()
{
}

void AirQualityModule::changeMuxChanel(uint8_t chanel)
{
	digitalWrite(muxIn1, (chanel & 0x01) ? HIGH : LOW);
	digitalWrite(muxIn2, (chanel & 0x02) ? HIGH : LOW);
}