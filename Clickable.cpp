#include "Clickable.h"
#include "ServiceLocator.h"

Clickable::Clickable()
{
	ServiceLocator::getEventService()->listen(typeid(Events::MouseEvents::ClickEvent), EventCallback(&Clickable::onClick, this));

}


Clickable::~Clickable()
{
}
