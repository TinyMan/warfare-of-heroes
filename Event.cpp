#include "Event.h"
#include "ServiceLocator.h"
namespace Events
{
	Event::~Event()
	{
	}
	void Event::dispatch()
	{
		EVENTSERVICE->dispatch(this);
	}
}