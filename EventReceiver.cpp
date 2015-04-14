#include "EventReceiver.h"
#include "ServiceLocator.h"

EventReceiver::EventReceiver(const type_info& ti)
{
	ServiceLocator::getEventService()->listen(ti, EventCallback(&EventReceiver::onEvent, this));
}


EventReceiver::~EventReceiver()
{
}

void EventReceiver::onEvent(Event* e)
{
	if (concernMe(e) && _cb)		
	{
		_cb->call(e);
	}
}