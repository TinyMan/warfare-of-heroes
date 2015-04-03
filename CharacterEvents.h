#pragma once
#include "Event.h"
class Character;


namespace Events
{
	namespace CharacterEvents
	{
		class Event : public Events::Event
		{
		public:
			Event(Character* c) : _character(c){}
			virtual ~Event(){}
			Character* getCharacter() const { return _character; }
		private:
			Character* _character;
		};
		class DieEvent : public Event
		{
		public:
			DieEvent(Character* c) : Event(c) {}
			virtual ~DieEvent(){}
		};
	}
}