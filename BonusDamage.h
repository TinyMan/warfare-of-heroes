#pragma once
#include "DamageOverTime.h"
class BonusDamage :
	public DamageOverTime
{
public:
	BonusDamage(int dmg = 0, int duration = 0, string name = "Unknown Damage Buff", SpellTarget * t = nullptr);	

	virtual ~BonusDamage();

	virtual int getBonus() const { return _damage; }
};

