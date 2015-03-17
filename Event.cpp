#include "Event.h"


Event::Event(EVENT_TYPE type, void* data) : _type(type), _data(data)
{
}


Event::~Event()
{
}

/*void Event::dispatch() const
{
	getEventService()->dispatch(*this);
}*/