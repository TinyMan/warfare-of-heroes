#pragma once
#include <iostream>
#include "Event.h"
using namespace std;

namespace Events
{
	namespace SpellEvents
	{
		class SpellEvent : public Events::Event
		{
		public:
			SpellEvent(string spellName) : _name(spellName){}
			virtual ~SpellEvent(){};
			string name() const { return _name; }
		private:
			string _name;
		};
		class SpellCastEvent : public SpellEvent
		{
		public:
			SpellCastEvent(string spellName) : SpellEvent(spellName){}
			virtual ~SpellCastEvent(){}
		};
	}
}