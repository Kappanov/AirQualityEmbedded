#ifndef MQ5_SENSOR_H
#define MQ5_SENSOR_H

#include <cstdint>
#include <data/MQ5SensorData.h>

class MQ5Sensor {
private:
	uint8_t pin;
	
public:
	MQ5Sensor(uint8_t pin);
	MQ5SensorData readSensor();
};

#endif 