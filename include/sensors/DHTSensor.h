#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <Arduino.h>
#include <DHT.h>

#include <cstdint>
#include <data/DHTSensorData.h>

class DHTSensor
{
private:
	uint8_t pin;
	DHT *dht;

public:
	DHTSensor(uint8_t pin);
	DHTSensorData readSensor();
};

#endif