#pragma once
#include "DamageOverTime.h"
class BonusDamage :
	public DamageOverTime
{
public:
	BonusDamage(int dmg = 0, int duration = 0, string name = "Unknown Damage Buff", SpellTarget * t = nullptr);	

	virtual ~BonusDamage();

	virtual int getBonus() const { if (_duration > 0) return _damage; return 0; }
	virtual void beginTurn();

};

