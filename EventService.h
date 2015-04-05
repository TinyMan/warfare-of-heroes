#pragma once
#include <typeinfo>
#include <list>
#include <map>
#include <iostream>
#include "Event.h"
#include "Callback.h"

using namespace std;
#define EVENTSERVICE ServiceLocator::getEventService()

namespace Events
{
	class EventService
	{
	public:
		EventService();
		virtual ~EventService();

		virtual void dispatch(Event*) const;

		void listen(const type_info& e, const Callback& cb);

	private:
		map<size_t, list<Callback>> _listeners;

	};
}

