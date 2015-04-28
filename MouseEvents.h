#pragma once
#include <SDL2/SDL.h>
#include "Event.h"

namespace Events
{
	namespace MouseEvents
	{
		class MouseEvent : public Events::Event
		{
		public:
			MouseEvent(SDL_Point p) : _pos(p) {}
			MouseEvent(int x, int y) : _pos({ x, y }) {}
			~MouseEvent() {}
			SDL_Point getPos() const { return _pos; }
		private:
			SDL_Point _pos;
		};
		class ClickEvent : public MouseEvent
		{
		public:
			ClickEvent(SDL_Point p, Uint8 button = SDL_BUTTON_LEFT) : MouseEvent(p), _button(button){ _last_click = SDL_GetTicks(); }
			ClickEvent(int x, int y, Uint8 button = SDL_BUTTON_LEFT) : MouseEvent(x, y), _button(button){ _last_click = SDL_GetTicks(); }
			virtual ~ClickEvent(){ }
			Uint8 button() const { return _button; }
			static bool canClick() { return getTimeBetweenClicks() + _last_click < SDL_GetTicks(); }
			static Uint32 getTimeBetweenClicks() { return _time_between_clicks; }
		private:
			Uint8 _button;
			static Uint32 _last_click;
			static const Uint32 _time_between_clicks; // milliseconds
		};
		class MotionEvent : public MouseEvent
		{
		public:
			MotionEvent(SDL_Point p) : MouseEvent(p) {}
			MotionEvent(int x, int y) : MouseEvent(x, y) {}
			virtual ~MotionEvent(){ }
		};
	}
}
