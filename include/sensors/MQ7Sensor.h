#ifndef MQ7SENSOR_H
#define MQ7SENSOR_H

#include <Arduino.h>
#include <cstdint>
#include <data/Action.h>

class MQ7Sensor
{
private:
	uint8_t pin;
	uint8_t interruptPin;
	const float THRESHOLD = 1000.0; // Порог в ppm для CO

public:
	MQ7Sensor(uint8_t pin, uint8_t interruptPin);
	float readSensor();
	void onRisingEdge(Action);
	bool isThresholdExceeded();
};

#endif