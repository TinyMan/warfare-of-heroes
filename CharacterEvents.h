#pragma once
#include "Event.h"
class Character;
class Cell;

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
		class MoveEvent : public CharacterEvent
		{
		public:
			MoveEvent(Character* c, Cell* _origin, Cell* dst) : CharacterEvent(c), destination(dst), origin(_origin) {}
			virtual ~MoveEvent(){}
			Cell* destination;
			Cell* origin;
		};
		class DieEvent : public CharacterEvent
		{
		public:
			DieEvent(Character* c) : CharacterEvent(c) {}
			virtual ~DieEvent(){}
		};
		/* losing and gaining stat trigger these */
		class LoseGainStatEvent : public CharacterEvent
		{
		public:
			LoseGainStatEvent(Character* c, int amount) : CharacterEvent(c), _amount(amount) {}
			virtual ~LoseGainStatEvent(){}
			int getAmount() const { return _amount; }
		private:
			int _amount;
		};
		class LoseHpEvent : public LoseGainStatEvent
		{
		public:
			LoseHpEvent(Character* c, int amount) : LoseGainStatEvent(c, amount){}
			virtual ~LoseHpEvent(){}
		};
		class GainHPEvent : public LoseGainStatEvent
		{
		public:
			GainHPEvent(Character* c, int amount) : LoseGainStatEvent(c, amount){}
			virtual ~GainHPEvent(){}
		};
		class LoseMPEvent : public LoseGainStatEvent
		{
		public:
			LoseMPEvent(Character* c, int amount) : LoseGainStatEvent(c, amount) {}
			virtual ~LoseMPEvent(){}
		};
		class GainMPEvent : public LoseGainStatEvent
		{
		public:
			GainMPEvent(Character* c, int amount) : LoseGainStatEvent(c, amount){}
			virtual ~GainMPEvent(){}
		};
		class LoseCPEvent : public LoseGainStatEvent
		{
		public:
			LoseCPEvent(Character* c, int amount) : LoseGainStatEvent(c, amount) {}
			virtual ~LoseCPEvent(){}
		};
		class GainCPEvent : public LoseGainStatEvent
		{
		public:
			GainCPEvent(Character* c, int amount) : LoseGainStatEvent(c, amount){}
			virtual ~GainCPEvent(){}
		};
	}
}