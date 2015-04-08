#include "Clickable.h"
#include "ServiceLocator.h"

Clickable::Clickable()
{
	ServiceLocator::getEventService()->listen(typeid(Events::MouseEvents::LeftClick), EventCallback(&Clickable::onClick, this));
	ServiceLocator::getEventService()->listen(typeid(Events::MouseEvents::RightClick), EventCallback(&Clickable::onClick, this));

}


Clickable::~Clickable()
{
}
