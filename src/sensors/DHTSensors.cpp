#include <sensors/DHTSensor.h>

DHTSensor::DHTSensor(DHT *dht) : dht(dht)
{
	dht->begin();

	Serial.println("DHTSensor created");
}

DHTSensorData DHTSensor::readSensor()
{
	DHTSensorData data;
	data.humidity = dht->readHumidity();
	data.temperature = dht->readTemperature();

	return data;
}