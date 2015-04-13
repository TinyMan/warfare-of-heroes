#include "EventService.h"
#include "ServiceLocator.h"

namespace Events
{
	EventService::EventService()
	{
	}


	EventService::~EventService()
	{
	}


	void EventService::dispatch(Event* e) const
	{
		//LOGINFO << "Dispatching " << typeid(*e).name() << endl;
		if (!_listeners.count(typeid(*e).hash_code()))
			return;
		for (auto& cb : _listeners.at(typeid(*e).hash_code()))
		{
			cb.call(e);
		}
	}

	void EventService::listen(const type_info& ti, const EventCallback& cb)
	{
		_listeners[ti.hash_code()].push_back(cb);
	}
}