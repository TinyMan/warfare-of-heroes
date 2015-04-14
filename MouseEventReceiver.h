#pragma once
#include <SDL2/SDL.h>
#include "EventReceiver.h"
#include "MouseEvents.h"

class MouseEventReceiver :
	public EventReceiver
{
public:
	MouseEventReceiver(const type_info& event);
	virtual ~MouseEventReceiver();

	virtual bool isInArea(SDL_Point) const = 0;
	virtual bool concernMe(Event* e) const
	{
		return isInArea(((MouseEvents::ClickEvent*)e)->getPos());
	}
};

