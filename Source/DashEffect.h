#pragma once
#include "MoveEffect.h"
class DashEffect :
	public MoveEffect
{
public:
	DashEffect(Character* caster = nullptr);
	virtual ~DashEffect();

	virtual bool apply(SpellTarget* target);

};

