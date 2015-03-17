#pragma once
#include <list>
#include <map>
#include <iostream>
#include "Event.h"
#include "Callback.h"

using namespace std;

class EventService
{
public:
	EventService();
	virtual ~EventService();

	virtual void dispatch(Event&) const;
	
	void listen(Event::EVENT_TYPE e, Callback& cb);

private:
	map<Event::EVENT_TYPE, list<Callback>> _listeners;

};

