#include <Arduino.h>
#include <sensors/MQ7Sensor.h>

MQ7Sensor::MQ7Sensor(uint8_t pin) : pin(pin)
{
	pinMode(pin, INPUT);
}

float MQ7Sensor::readSensor()
{
	int rawValue = analogRead(pin);
	float voltage = rawValue * (5.0 / 1023.0);
	return voltage;
}