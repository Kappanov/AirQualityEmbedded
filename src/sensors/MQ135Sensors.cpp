#include <Arduino.h>
#include <sensors/MQ135Sensor.h>
#include <data/MQ135SensorData.h>

MQ135Sensor::MQ135Sensor(uint8_t pin) : pin(pin)
{
	pinMode(pin, INPUT);
}

MQ135SensorData MQ135Sensor::readSensor()
{
	int rawValue = analogRead(pin);
	float voltage = rawValue * (5.0 / 1023.0);
	MQ135SensorData data;
	data.benzene = voltage * 0.1; // Example conversion factor for benzene
	data.co2 = voltage * 0.2;	  // Example conversion factor for CO2
	data.nh3 = voltage * 0.3;	  // Example conversion factor for NH3
	data.smoke = voltage * 0.4;	  // Example conversion factor for smoke
	return data;
}