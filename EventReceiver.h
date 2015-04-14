#pragma once
#include "Event.h"
#include "EventCallback.h"
#include "Modifiable.h"
using namespace Events;

class EventReceiver
	: public Modifiable
{
public:
	EventReceiver() {}
	EventReceiver(const type_info& ti);
	virtual ~EventReceiver();

	virtual void onEvent(Event*);
	virtual void setCallback(EventCallback* cb){ _cb = cb; }

	virtual bool concernMe(Event*) const = 0;
	void addEventToListen(const type_info& ti);

private:
	EventCallback* _cb;
};

