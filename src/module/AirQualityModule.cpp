#include <module/AirQualityModule.h>

AirQualityModule::AirQualityModule(DHTSensor *dhtSensor, MQ135Sensor *mq135sensor, MQ5Sensor *mq5sensor,
								   MQ7Sensor *mq7sensor, uint8_t muxIn1, uint8_t muxIn2, uint8_t muxIn3)
	: dhtSensor(dhtSensor), mq135sensor(mq135sensor), mq5sensor(mq5sensor), mq7sensor(mq7sensor),
	  muxIn1(muxIn1), muxIn2(muxIn2), muxIn3(muxIn3)
{
	pinMode(muxIn1, OUTPUT);
	pinMode(muxIn2, OUTPUT);
	pinMode(muxIn3, OUTPUT);

	status = DeviceStatus::ACTIVE;
	sendingDataTimer.attach_ms(SENDING_DATA_INTERVAL_MS, [this]()
							   {
    if (status == DeviceStatus::ACTIVE && callbackForSendingData) {
      callbackForSendingData();
    } });

	Serial.println("AirQualityModule created");
}

AirQualityModule::~AirQualityModule() {}

AirQuality AirQualityModule::getAirQuality()
{
	AirQuality airQuality;

	changeMuxChanel(0); // MQ5
	auto mq5data = mq5sensor->readSensor();

	changeMuxChanel(1); // MQ7
	airQuality.coPpm = mq7sensor->readSensor();

	changeMuxChanel(2); // MQ135
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

void AirQualityModule::changeMuxChanel(uint8_t chanel)
{
	digitalWrite(muxIn1, (chanel & 0x01) ? HIGH : LOW);
	digitalWrite(muxIn2, (chanel & 0x02) ? HIGH : LOW);
	digitalWrite(muxIn3, (chanel & 0x04) ? HIGH : LOW);
	delay(10); // Allow multiplexer to settle
}

void AirQualityModule::changeStatus(DeviceStatus newStatus)
{
	status = newStatus;
	if (status == DeviceStatus::ACTIVE)
	{
		sendingDataTimer.attach_ms(SENDING_DATA_INTERVAL_MS, [this]()
								   {
      if (status == DeviceStatus::ACTIVE && callbackForSendingData) {
        callbackForSendingData();
      } });
	}
	else
	{
		sendingDataTimer.detach();
	}
}

DeviceStatus AirQualityModule::getStatus()
{
	return status;
}

void AirQualityModule::onSendingData(Action callback)
{
	callbackForSendingData = callback;
}