#include "Clickable.h"
#include "ServiceLocator.h"

Clickable::Clickable()
{
	ServiceLocator::getEventService()->listen(typeid(Events::MouseEvents::LeftClick), EventCallback(&Clickable::onLeftClick, this));
	ServiceLocator::getEventService()->listen(typeid(Events::MouseEvents::RightClick), EventCallback(&Clickable::onRightClick, this));

}


Clickable::~Clickable()
{
}
