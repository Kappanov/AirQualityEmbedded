#include <sensors/MQ135Sensor.h>

MQ135Sensor::MQ135Sensor(uint8_t pin) : pin(pin)
{
	pinMode(pin, INPUT);
	Serial.println("MQ135Sensor created");
}

MQ135SensorData MQ135Sensor::readSensor()
{
	int rawValue = analogRead(pin);
	float voltage = rawValue * (3.3 / 1023.0); // ESP8266 с делителем
	MQ135SensorData data;
	// Упрощённые коэффициенты, замените на калибровочные
	data.benzene = voltage / 100; // C6H6
	data.co2 = pow(voltage, voltage) * 200;	  // CO2
	data.nh3 = voltage * 2;	  // NH3
	data.smoke = voltage * 400;	  // Smoke
	return data;
}

bool MQ135Sensor::isThresholdExceeded()
{
	MQ135SensorData data = readSensor();
	return data.co2 > THRESHOLD;
}  