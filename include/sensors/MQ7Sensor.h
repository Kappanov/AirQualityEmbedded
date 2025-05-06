#ifndef MQ7SENSOR_H
#define MQ7SENSOR_H

#include <cstdint>
#include <data/Action.h>

class MQ7Sensor
{
private:
	uint8_t pin;
	uint8_t interruptPin;

public:
	MQ7Sensor(uint8_t pin, uint8_t interruptPin);
	float readSensor();
	void onRisingEdge(Action);
};

#endif // MQ7SENSOR_H