#pragma once
#include <SDL2/SDL.h>
#include "MouseEvents.h"
using namespace Events;

class Clickable
{
public:
	Clickable();
	virtual ~Clickable();

	virtual bool isInArea(SDL_Point) = 0;

	virtual void onClick(Event* e) { _cb.call(e); }
	virtual void onClick(EventCallback& cb){ _cb = cb; }

private:
	EventCallback _cb;

};
