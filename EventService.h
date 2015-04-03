#pragma once
#include <list>
#include <map>
#include <iostream>
#include "Event.h"
#include "Callback.h"

using namespace std;

namespace Events
{
	class EventService
	{
	public:
		EventService();
		virtual ~EventService();

		virtual void dispatch(Event&) const;

		void listen(EVENT_TYPE e, Callback& cb);

	private:
		map<EVENT_TYPE, list<Callback>> _listeners;

	};
}

