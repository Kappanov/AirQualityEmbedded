#ifndef AIR_QUALITY_DEVICE_H
#define AIR_QUALITY_DEVICE_H

#include <Arduino.h>
#include <ctime>
#include <data/AirQuality.h>
#include <data/Action.h>
#include <enum/DeviceStatus.h>
#include <sensors/DHTSensor.h>
#include <sensors/MQ5Sensor.h>
#include <sensors/MQ7Sensor.h>
#include <sensors/MQ135Sensor.h>

#define SENDING_DATA_INTERVAL_MS 0.5 * 60 * 1000 // 60 секунд

class AirQualityModule {
private:
  DHTSensor *dhtSensor;
  MQ135Sensor *mq135sensor;
  MQ5Sensor *mq5sensor;
  MQ7Sensor *mq7sensor;
  Action callbackForSendingData;
  uint8_t muxIn1, muxIn2, muxIn3;
  volatile DeviceStatus status;
  unsigned long lastSendTime; // Для программного таймера

  void changeMuxChanel(uint8_t);

public:
  AirQualityModule(DHTSensor *dhtSensor, MQ135Sensor *mq135sensor, MQ5Sensor *mq5sensor, MQ7Sensor *mq7sensor,
                   uint8_t muxIn1, uint8_t muxIn2, uint8_t muxIn3);
  ~AirQualityModule();
  AirQuality getAirQuality();
  void onRisingEdge(Action callback);
  void onSendingData(Action callback);
  void changeStatus(DeviceStatus newStatus);
  DeviceStatus getStatus();
  void loop(); // Добавляем метод loop для обработки таймера
};

#endif