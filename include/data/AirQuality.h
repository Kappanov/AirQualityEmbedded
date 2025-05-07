#ifndef AIR_QUALITY_H
#define AIR_QUALITY_H

#include <ctime>

struct AirQuality
{
	float temperature = 0.0f; // Температура
	float humidity = 0.0f;	  // Влажность
	float co2Ppm = 0.0f;	  // Углекислый газ (CO2) в ppm
	float nh3Ppm = 0.0f;	  // Аммиак (NH3) в ppm
	float benzenePpm = 0.0f;  // Бензол (C6H6) в ppm
	float lpgPpm = 0.0f;	  // Сжиженный нефтяной газ (LPG) в ppm
	float coPpm = 0.0f;		  // Угарный газ (CO) в ppm
	time_t timestamp = 0;	  // Временная метка

	const char *toJson() const;
};

#endif