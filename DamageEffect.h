#pragma once
#include "Effect.h"
class DamageEffect :
	public Effect
{
public:
	DamageEffect(int dmg, Character* caster=nullptr);
	virtual ~DamageEffect();

	virtual bool apply(SpellTarget* target);

protected:
	int _damage;
};

