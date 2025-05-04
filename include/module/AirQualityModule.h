#ifndef AIR_QUALITY_DEVICE_H
#define AIR_QUALITY_DEVICE_H

#include <data/AirQuality.h>
#include <data/Action.h>

#include <sensors/DHTSensor.h>
#include <sensors/MQ135Sensor.h>
#include <sensors/MQ5Sensor.h>
#include <sensors/MQ7Sensor.h>

class AirQualityModule {
private:
	DHTSensor* dhtSensor;
	MQ135Sensor* mq135sensor;
	MQ5Sensor* mq5sensor;
	MQ7Sensor* mq7sensor;
	Action* callbackOnRisingEdge;

public:
	AirQualityModule(DHTSensor* dhtSensor, MQ135Sensor* mq135sensor, MQ5Sensor* mq5sensor, MQ7Sensor* mq7sensor);
	~AirQualityModule();
	
	AirQuality getAirQuality();
	void onRisingEdge(Action callback);
};


#endif