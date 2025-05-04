#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <cstdint>
#include <data/DHTSensorData.h>

class DHTSensor
{
private:
	uint8_t pin;

public:
	DHTSensor(uint8_t pin);
	DHTSensorData readSensor();
};

#endif