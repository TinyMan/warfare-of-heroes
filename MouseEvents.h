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
			ClickEvent(SDL_Point p) : _pos(p){}
			virtual ~ClickEvent(){ }
		private:
			SDL_Point _pos;
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
