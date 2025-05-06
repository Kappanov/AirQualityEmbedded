#include <Arduino.h>
#include <sensors/MQ7Sensor.h>

MQ7Sensor::MQ7Sensor(uint8_t pin, uint8_t interruptPin) : pin(pin), interruptPin(interruptPin)
{
	pinMode(pin, INPUT);
	Serial.println("MQ7Sensor created");
}

float MQ7Sensor::readSensor()
{
	int rawValue = analogRead(pin);
	float voltage = rawValue * (5.0 / 1023.0);
	return voltage;
}

void MQ7Sensor::onRisingEdge(Action callback)
{
	attachInterrupt(digitalPinToInterrupt(interruptPin), callback, RISING);
}