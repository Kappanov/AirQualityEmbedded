#include <data/AirQuality.h>

#include <cstdio>  // для sprintf
#include <cstring> // для strcpy
#include <cstdlib> // для malloc/free

const char *AirQuality::toJson()
{
	static char jsonBuffer[256];

	snprintf(jsonBuffer, sizeof(jsonBuffer),
			 "{\"temperature\":%.2f,\"humidity\":%.2f,\"co2Ppm\":%.2f,"
			 "\"nh3Ppm\":%.2f,\"benzenePpm\":%.2f,\"lpgPpm\":%.2f,"
			 "\"coPpm\":%.2f,\"timestamp\":%ld}",
			 temperature, humidity, co2Ppm,
			 nh3Ppm, benzenePpm, lpgPpm,
			 coPpm, static_cast<long>(timestamp));

	return jsonBuffer;
}