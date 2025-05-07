#include <sensors/MQ5Sensor.h>

MQ5Sensor::MQ5Sensor(uint8_t pin) : pin(pin)
{
	pinMode(pin, INPUT);
	Serial.println("MQ5Sensor created");
}

MQ5SensorData MQ5Sensor::readSensor()
{
	int rawValue = analogRead(pin);
	float voltage = rawValue * (3.3 / 1023.0); // ESP8266 с делителем
	MQ5SensorData data;
	// Упрощённые коэффициенты, замените на калибровочные
	data.carbonMonoxide = voltage * 200; // CO
	data.hydrogen = voltage * 300;		 // H2
	data.lpg = voltage * 100;			 // LPG
	data.methane = voltage * 150;		 // CH4
	data.propane = voltage * 100;		 // C3H8
	return data;
}

bool MQ5Sensor::isThresholdExceeded()
{
	MQ5SensorData data = readSensor();
	return data.lpg > THRESHOLD;
}