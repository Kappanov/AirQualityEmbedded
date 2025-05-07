#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <cstdint>
#include <data/DHTSensorData.h>

class DHTSensor
{
private:
	uint8_t pin;
	DHT *dht;
	unsigned long lastReadTime;

public:
	DHTSensor(uint8_t pin);
	~DHTSensor();
	DHTSensorData readSensor();
};

#endif