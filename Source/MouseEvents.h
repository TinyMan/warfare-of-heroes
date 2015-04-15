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
			ClickEvent(SDL_Point p, Uint8 button = SDL_BUTTON_LEFT) : MouseEvent(p), _button(button){}
			ClickEvent(int x, int y, Uint8 button = SDL_BUTTON_LEFT) : MouseEvent(x, y), _button(button){}
			virtual ~ClickEvent(){ }
			Uint8 button() const { return _button; }
		private:
			Uint8 _button;
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
