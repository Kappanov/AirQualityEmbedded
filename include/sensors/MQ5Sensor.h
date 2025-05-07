#ifndef MQ5_SENSOR_H
#define MQ5_SENSOR_H

#include <Arduino.h>
#include <cstdint>
#include <data/MQ5SensorData.h>

class MQ5Sensor
{
private:
	uint8_t pin;
	const float THRESHOLD = 1000.0; // Порог в ppm для LPG

public:
	MQ5Sensor(uint8_t pin);
	MQ5SensorData readSensor();
	bool isThresholdExceeded();
};

#endif