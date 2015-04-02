#pragma once
#include "OverTimeEffect.h"
#include "DamageEffect.h"

class DamageBuffEffect :
	public OverTimeEffect
{
public:
	DamageBuffEffect(int amount = 0, int duration = 0, Character* caster = nullptr);
	virtual ~DamageBuffEffect();
	
	virtual bool beginTurn(); 
	virtual DamageBuffEffect* clone() const {
		return new DamageBuffEffect(*this);
	}
protected:
	int _amount;
};

