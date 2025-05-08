#include <sensors/MQ7Sensor.h>

MQ7Sensor::MQ7Sensor(uint8_t pin, uint8_t interruptPin) : pin(pin), interruptPin(interruptPin)
{
	pinMode(pin, INPUT);
	pinMode(interruptPin, INPUT_PULLUP);
	Serial.println("MQ7Sensor created");
}

float MQ7Sensor::readSensor()
{
	int rawValue = analogRead(pin);
	float voltage = rawValue * (3.3 / 1023.0); // ESP8266 с делителем
	return pow(voltage, voltage) * 20;					   // Упрощённый расчёт CO в ppm, замените на калибровочный
}

void MQ7Sensor::onRisingEdge(Action callback)
{
	attachInterrupt(digitalPinToInterrupt(interruptPin), callback, FALLING); // FALLING для DOUT
}

bool MQ7Sensor::isThresholdExceeded()
{
	return readSensor() > THRESHOLD;
}