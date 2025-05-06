#include <sensors/DHTSensor.h>

DHTSensor::DHTSensor(uint8_t pin) : pin(pin)
{
	pinMode(pin, INPUT);
	dht = new DHT(pin, DHT11);
	dht->begin();
}

DHTSensorData DHTSensor::readSensor()
{
	DHTSensorData data;
	data.humidity = dht->readHumidity();
	data.temperature = dht->readTemperature();

	return data;
}