#include "Hoverable.h"
#include "ServiceLocator.h"

Hoverable::Hoverable() : MouseEventReceiver(typeid(Events::MouseEvents::ClickEvent))
{
}


Hoverable::~Hoverable()
{
}
