#pragma once
#include <SDL2/SDL.h>
#include "Event.h"

namespace Events
{
	namespace MouseEvents
	{
		class ClickEvent : public Events::Event
		{
		public:
			ClickEvent(SDL_Point p, bool left = true) : _pos(p), _left(left){}
			virtual ~ClickEvent(){ }
			bool isLeft() const { return _left; }
			bool isRight() const { return !_left; }
		private:
			SDL_Point _pos;
			bool _left;
		};
		class LeftClick : public ClickEvent
		{
		public:
			LeftClick(SDL_Point p) : ClickEvent(p) {}
			virtual ~LeftClick(){}
		};
		class RightClick : public ClickEvent
		{
		public:
			RightClick(SDL_Point p) : ClickEvent(p) {}
			virtual ~RightClick(){}
		};
	}
}
