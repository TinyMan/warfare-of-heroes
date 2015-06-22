#pragma once
#include <iostream>
#include "Event.h"
using namespace std;

class Spell;
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
			SpellCastEvent(Spell * s) : SpellEvent(s){}
			virtual ~SpellCastEvent(){}
		};
	}
}