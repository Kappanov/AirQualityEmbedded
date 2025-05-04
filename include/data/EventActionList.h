#ifndef EVENT_ACTION_LIST_H
#define EVENT_ACTION_LIST_H

#include <data/EventAction.h>
#include <cstdint>

class EventActionList {
private:
	EventAction* eventActions;
	uint8_t eventCount;

public:
	EventActionList();
	~EventActionList();

	void AddEventAction(const EventAction* eventAction);
	void AddEventAction(const char* event, Action action);
	void RemoveEventAction(const char* event);
	void RemoveEventAction(const EventAction* eventAction);
};

#endif