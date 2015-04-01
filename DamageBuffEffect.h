#pragma once
#include "OverTimeEffect.h"
#include "DamageEffect.h"

class DamageBuffEffect :
	public OverTimeEffect
{
public:
	DamageBuffEffect(int amount = 0, int duration = 0, Character* caster = nullptr);
	virtual ~DamageBuffEffect();

	virtual bool apply(SpellTarget* target) { return OverTimeEffect::apply(target); }

	virtual bool beginTurn();
protected:
	int _amount;
};

