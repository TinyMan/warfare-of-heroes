#pragma once
#include <iostream>
#include "Event.h"
using namespace std;

class Spell;
class SpellTarget;
namespace Events
{
	namespace SpellEvents
	{
		class SpellEvent : public Events::Event
		{
		public:
			SpellEvent(Spell * s) : spell(s){}
			virtual ~SpellEvent(){};
			Spell* spell;
		};
		class SpellCastEvent : public SpellEvent
		{
		public:
			SpellCastEvent(Spell * s, SpellTarget* t) : SpellEvent(s), target(t){}
			virtual ~SpellCastEvent(){}
			SpellTarget *target;
		};
	}
}