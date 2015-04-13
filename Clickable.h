#pragma once
#include <SDL2/SDL.h>
#include "MouseEvents.h"
#include "EventCallback.h"

using namespace Events;

class Clickable
{
public:
	Clickable();
	virtual ~Clickable();

	virtual bool isInArea(SDL_Point) const = 0;

	virtual void onClick(Event* e);
	virtual void setCallback(EventCallback* cb){ _cb = cb; }

private:
	EventCallback* _cb;

};
