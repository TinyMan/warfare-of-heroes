#include "Hoverable.h"
#include "ServiceLocator.h"
#include "MouseEvents.h"
#include "Tooltip.h"

Hoverable::Hoverable() : MouseEventReceiver(typeid(Events::MouseEvents::MotionEvent))
{
	setCallback(new EventCallback(
		[this](Event* e) 
	{
		if (isInArea(((MouseEvents::MouseEvent*)e)->getPos()))
			onMouseIn((MouseEvents::MotionEvent*)e);
		else
			onMouseOut((MouseEvents::MotionEvent*)e);
		setDirty();
	}));
}


Hoverable::~Hoverable()
{
}
void Hoverable::onMouseIn(MouseEvents::MotionEvent* e)
{ 
	_hover = true; 	
}
void Hoverable::onMouseOut(MouseEvents::MotionEvent* e)
{
	_hover = false;	
}