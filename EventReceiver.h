#pragma once
#include "Event.h"
#include "EventCallback.h"
using namespace Events;

class EventReceiver
{
public:
	EventReceiver(const type_info& ti);
	virtual ~EventReceiver();

	virtual void onEvent(Event*);
	virtual void setCallback(EventCallback* cb){ _cb = cb; }

	virtual bool concernMe(Event*) const = 0;
private:
	EventCallback* _cb;
};

