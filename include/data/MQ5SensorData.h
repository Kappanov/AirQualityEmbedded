#ifndef MQ5_SENSOR_DATA_H
#define MQ5_SENSOR_DATA_H

#include <cstdint>

// Структура для хранения данных веществ, получаемых с датчика MQ5
struct MQ5SensorData {
	float methane;       // Концентрация метана (CH4) в ppm
	float propane;       // Концентрация пропана (C3H8) в ppm
	float hydrogen;      // Концентрация водорода (H2) в ppm
	float carbonMonoxide; // Концентрация угарного газа (CO) в ppm
	float alcohol;       // Концентрация алкоголя (C2H5OH) в ppm
	float lpg;

	MQ5SensorData()
		: methane(0.0f), propane(0.0f), hydrogen(0.0f), carbonMonoxide(0.0f), alcohol(0.0f), lpg(0.0f) {}
};

#endif