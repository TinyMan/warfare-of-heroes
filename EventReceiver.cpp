#include "EventReceiver.h"
#include "ServiceLocator.h"
#include "MyContainer.h"

EventReceiver::EventReceiver(const type_info& ti)
{
	addEventToListen(ti);
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
void EventReceiver::addEventToListen(const type_info& ti)
{
	ServiceLocator::getEventService()->listen(ti, EventCallback(&EventReceiver::onEvent, this));
}