#ifndef MQ135SENSOR_H
#define MQ135SENSOR_H

#include <stdint.h>
#include <data/MQ135SensorData.h>

class MQ135Sensor
{
private:
	uint8_t pin;

public:
	MQ135Sensor(uint8_t pin);
	MQ135SensorData readSensor();
};

#endif // MQ135SENSOR_H