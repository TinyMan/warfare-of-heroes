#include "Hoverable.h"
#include "ServiceLocator.h"
#include "MouseEvents.h"

Hoverable::Hoverable() : MouseEventReceiver(typeid(Events::MouseEvents::MotionEvent))
{
	setCallback(new EventCallback(
		[this](Event* e) 
	{
		if (isInArea(((MouseEvents::MouseEvent*)e)->getPos()))
			_hover = true;
		else
			_hover = false;
		triggerModifyEvent();
	}));
}


Hoverable::~Hoverable()
{
}
