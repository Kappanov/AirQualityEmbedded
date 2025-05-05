#include <module/AirQualityModule.h>
#include <ctime>

AirQualityModule::AirQualityModule(
	DHTSensor *dhtSensor,
	MQ135Sensor *mq135sensor,
	MQ5Sensor *mq5sensor,
	MQ7Sensor *mq7sensor)
	: dhtSensor(dhtSensor), mq135sensor(mq135sensor), mq5sensor(mq5sensor), mq7sensor(mq7sensor) {}

AirQuality AirQualityModule::getAirQuality()
{
	AirQuality airQuality;

	auto mq5data = mq5sensor->readSensor();
	auto mq135data = mq135sensor->readSensor();
	auto dhtData = dhtSensor->readSensor();

	airQuality.coPpm = mq7sensor->readSensor();
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