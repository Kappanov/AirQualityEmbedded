#ifndef MQ135DATA_H
#define MQ135DATA_H

#include <cstdint>

struct MQ135SensorData {
	float co2;          // Концентрация CO2 в ppm
	float nh3;          // Концентрация аммиака (NH3) в ppm
	float benzene;      // Концентрация бензола в ppm
	float smoke;        // Концентрация дыма в ppm

	MQ135SensorData()
		: co2(0.0f), nh3(0.0f), benzene(0.0f), smoke(0.0f) {}
};

#endif