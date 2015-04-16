#pragma once
#include "Event.h"
class Character;


namespace Events
{
	namespace CharacterEvents
	{
		class CharacterEvent : public Events::Event
		{
		public:
			CharacterEvent(Character* c) : _character(c){}
			virtual ~CharacterEvent(){}
			Character* getCharacter() const { return _character; }
		private:
			Character* _character;
		};
		class DieEvent : public CharacterEvent
		{
		public:
			DieEvent(Character* c) : CharacterEvent(c) {}
			virtual ~DieEvent(){}
		};
	}
}