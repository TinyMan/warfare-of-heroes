#include "Clickable.h"
#include "ServiceLocator.h"

Clickable::Clickable()
{
	ServiceLocator::getEventService()->listen(typeid(Events::MouseEvents::ClickEvent), EventCallback(&Clickable::onClick, this));

}


Clickable::~Clickable()
{
}

void Clickable::onClick(Event * e)
{ 
	if (isInArea(((MouseEvents::ClickEvent*)e)->getPos()) && _cb)
	{
		_cb->call(e); 
	}
}