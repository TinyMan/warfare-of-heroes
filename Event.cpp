#include "Event.h"
namespace Events
{
	int Event::next_id = 0;

	Event::Event(EVENT_TYPE type, void* data) : _type(type), _data(data), _id(next_id++)
	{
	}


	Event::~Event()
	{
	}

	/*void Event::dispatch() const
	{
	getEventService()->dispatch(*this);
	}*/
}