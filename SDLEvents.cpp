#include "SDLEvents.h"
#include "MouseEvents.h"
#include "ServiceLocator.h"
namespace Events
{
	namespace SDLEvents
	{
		Event* createEventFromSDLEvent(SDL_Event* e)
		{
			Event* event = nullptr;
			switch (e->type)
			{
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_MOUSEBUTTONUP:
				if (e->button.button == SDL_BUTTON_LEFT || e->button.button == SDL_BUTTON_RIGHT)
					if (MouseEvents::ClickEvent::canClick())
						event = new MouseEvents::ClickEvent(e->button.x, e->button.y, e->button.button);
				break;
			case SDL_MOUSEMOTION:
				event = new MouseEvents::MotionEvent(e->motion.x, e->motion.y);
				break;
			default:
				break;
			}
			return event;
		}
	}
}