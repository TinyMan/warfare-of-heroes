#pragma once
#include "Effect.h"
class HealEffect :
	public Effect
{
public:
	HealEffect(int heal = 0, Character* caster = nullptr);
	virtual ~HealEffect();

	virtual bool apply(SpellTarget* target);

protected:
	int _heal;
};

