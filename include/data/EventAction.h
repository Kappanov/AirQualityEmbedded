#ifndef EVENT_ACTION_H
#define EVENT_ACTION_H

#include <data/Action.h>

class EventAction {
private:
	const char* event;

public:
	Action action;
	EventAction(const char* event, Action action);
};

#endif