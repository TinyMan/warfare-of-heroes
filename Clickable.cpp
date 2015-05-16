#include "Clickable.h"


Clickable::Clickable() : MouseEventReceiver(typeid(Events::MouseEvents::ClickEvent))
{
	setCallback(new EventCallback(&Clickable::internalOnClick, this));
}


Clickable::~Clickable()
{
}
void Clickable::internalOnClick(Event* e)
{ 
	ClickEvent* ev = dynamic_cast<ClickEvent*>(e); 
	if (ev) 
		onClick(dynamic_cast<ClickEvent*>(e)); 
}
