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

	virtual void onClick(Event*) = 0;
	virtual void onLeftClick(Event* e) { onClick(e); }
	virtual void onRightClick(Event* e) { onClick(e); }

private:

};
