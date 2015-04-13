#include "Clickable.h"


Clickable::Clickable() : MouseEventReceiver(typeid(Events::MouseEvents::ClickEvent))
{
}


Clickable::~Clickable()
{
}
