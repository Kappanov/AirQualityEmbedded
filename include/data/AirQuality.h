#ifndef AIR_QUALITY_H
#define AIR_QUALITY_H

#include <ctime>

struct AirQuality {
	float Temperature;
	float Humidity;
	float Co2Ppm;
	float Nh3Ppm;
	float BenzenePpm;
	float LpgPpm;
	float CoPpm;
	std::time_t Timestamp;
};

#endif