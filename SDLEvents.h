#pragma once
#include <SDL2/SDL.h>
#include "Event.h"

namespace Events
{
	namespace SDLEvents
	{
		Event* createEventFromSDLEvent(SDL_Event* e);
	}
}