#ifndef AIR_QUALITY_DEVICE_H
#define AIR_QUALITY_DEVICE_H

#include <data/AirQuality.h>
#include <data/Action.h>

class AirQualityModule {
public:
	AirQuality getAirQuality();
	void onRisingEdge(Action callback);
};


#endif