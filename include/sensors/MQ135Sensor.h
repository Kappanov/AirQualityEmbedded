#ifndef MQ135SENSOR_H
#define MQ135SENSOR_H

#include <Arduino.h>
#include <cstdint>
#include <data/MQ135SensorData.h>

class MQ135Sensor
{
private:
	uint8_t pin;
	const float THRESHOLD = 1000.0; // Порог в ppm для CO2

public:
	MQ135Sensor(uint8_t pin);
	MQ135SensorData readSensor();
	bool isThresholdExceeded();
};

#endif