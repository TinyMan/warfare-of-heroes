#pragma once
#include "Effect.h"
class DamageEffect :
	public Effect
{
public:
	DamageEffect(int dmg, SpellTarget* target=nullptr);
	virtual ~DamageEffect();

	virtual bool apply(SpellTarget* target);

private:
	int _damage;
};

