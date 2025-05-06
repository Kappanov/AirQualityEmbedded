#include <Arduino.h>
#include <sensors/MQ5Sensor.h>
#include <data/MQ5SensorData.h>

MQ5Sensor::MQ5Sensor(uint8_t pin) : pin(pin)
{
	pinMode(pin, INPUT);
}

MQ5SensorData MQ5Sensor::readSensor()
{
	int rawValue = analogRead(pin);
	float voltage = rawValue * (5.0 / 1023.0);
	MQ5SensorData data;
	data.carbonMonoxide = voltage * 0.2; // Example conversion factor
	data.hydrogen = voltage * 0.3;		 // Example conversion factor
	data.lpg = voltage * 0.25;			 // Example conversion factor
	data.methane = voltage * 0.15;		 // Example conversion factor
	data.propane = voltage * 0.1;		 // Example conversion factor
	return data;
}