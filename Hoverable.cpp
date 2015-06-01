#include "Hoverable.h"
#include "ServiceLocator.h"
#include "MouseEvents.h"
#include "Tooltip.h"

Hoverable::Hoverable() : MouseEventReceiver(typeid(Events::MouseEvents::MotionEvent))
{
	setCallback(new EventCallback(
		[this](Event* e) 
	{
		bool b = isInArea(((MouseEvents::MouseEvent*)e)->getPos());
		if (b && !_hover)
			onMouseIn((MouseEvents::MotionEvent*)e);
		else if (b && _hover)
			onMouseMove((MouseEvents::MotionEvent*)e);
		else if (!b && _hover)
			onMouseOut((MouseEvents::MotionEvent*)e);
	}));
}


Hoverable::~Hoverable()
{
}
void Hoverable::onMouseIn(MouseEvents::MotionEvent* e)
{ 
	_hover = true;
	setDirty();
}
void Hoverable::onMouseOut(MouseEvents::MotionEvent* e)
{
	_hover = false;
	setDirty();
}
void Hoverable::onMouseMove(MouseEvents::MotionEvent* e)
{
	setDirty();
}