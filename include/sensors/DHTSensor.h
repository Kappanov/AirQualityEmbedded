#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <Arduino.h>
#include <DHT.h>

#include <cstdint>
#include <data/DHTSensorData.h>

class DHTSensor
{
private:
	DHT *dht;

public:
	DHTSensor(DHT *dht);
	DHTSensorData readSensor();
};

#endif