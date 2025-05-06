#ifndef AIR_QUALITY_DEVICE_H
#define AIR_QUALITY_DEVICE_H

#include <Arduino.h>
#include <Ticker.h>
#include <ctime>

#include <data/AirQuality.h>
#include <data/Action.h>
#include <enum/DeviceStatus.h>

#include <sensors/DHTSensor.h>
#include <sensors/MQ5Sensor.h>
#include <sensors/MQ7Sensor.h>
#include <sensors/MQ135Sensor.h>

#define SENDING_DATA_INTERVAL_MS 60 * 1000 // минута

class AirQualityModule
{
private:
	DHTSensor *dhtSensor;
	MQ135Sensor *mq135sensor;
	MQ5Sensor *mq5sensor;
	MQ7Sensor *mq7sensor;
	Action callbackForSendingData;

	uint8_t muxIn1;
	uint8_t muxIn2;

	volatile DeviceStatus status;
	Ticker sendingDataTimer;

	void changeMuxChanel(uint8_t);

public:
	AirQualityModule(DHTSensor *dhtSensor,
					 MQ135Sensor *mq135sensor,
					 MQ5Sensor *mq5sensor,
					 MQ7Sensor *mq7sensor,
					 uint8_t muxIn1, uint8_t muxIn2);
	~AirQualityModule();

	AirQuality getAirQuality();
	void onRisingEdge(Action callback);
	void onSendingData(Action callback);
	void changeStatus(DeviceStatus newStatus);
	DeviceStatus getStatus();
};

#endif