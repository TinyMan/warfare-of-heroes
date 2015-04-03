#include "EventService.h"

namespace Events
{
	EventService::EventService()
	{
	}


	EventService::~EventService()
	{
	}


	void EventService::dispatch(Event& e) const
	{
		if (!_listeners.count(e.getType()))
			return;
		for (auto cb : _listeners.at(e.getType()))
		{
			cb.call(&e);
		}
	}

	void EventService::listen(EVENT_TYPE et, Callback& cb)
	{
		_listeners[et].push_back(cb);
	}
}