#ifndef DEVICE_STATUS_H
#define DEVICE_STATUS_H

#include <cstdint>

enum DeviceStatus : uint8_t {
	ACTIVE,
	PASSIVE,
	POWEROFF
};

#endif