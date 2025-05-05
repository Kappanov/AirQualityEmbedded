#ifndef HUB_LIST_H
#define HUB_LIST_H

#include <cstdint>
#include <enum/Hubs.h>
#include <array>

struct HubList
{
	std::array<WebSocketsClient, 2> hubs;
	uint8_t count;
};

#endif