#include <sensors/DHTSensor.h>

DHTSensor::DHTSensor(uint8_t pin) : pin(pin), lastReadTime(0) {
  dht = new DHT(pin, DHT11);
  dht->begin();
  Serial.printf("DHTSensor initialized on pin %d, type %d\n", pin, DHT11);
}

DHTSensor::~DHTSensor() {
  delete dht;
}

DHTSensorData DHTSensor::readSensor() {
	DHTSensorData data = {0.0f, 0.0f};

  // Проверяем, прошло ли достаточно времени с последнего чтения (мин. 2 секунды)
  unsigned long currentTime = millis();
  if (currentTime - lastReadTime < 2000) {
    Serial.println("DHT: Too soon to read, returning last data or zeros");
    return data; // Возвращаем нули, чтобы избежать NaN
  }

  float temperature = dht->readTemperature();
  float humidity = dht->readHumidity();

  lastReadTime = currentTime;

  // Проверяем, вернул ли датчик NaN
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("DHT: Failed to read, returning zeros");
    return data; // Возвращаем нули вместо NaN
  }

  data.temperature = temperature;
  data.humidity = humidity;
  Serial.printf("DHT: Temperature = %.1f°C, Humidity = %.1f%%\n", temperature, humidity);

  return data;
}