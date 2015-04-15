#include "DashEffect.h"
#include "SpellTarget.h"
#include "Character.h"

DashEffect::DashEffect(Character* caster)
	: MoveEffect(nullptr, caster)
{
}


DashEffect::~DashEffect()
{
}

bool DashEffect::apply(SpellTarget* target)
{
	if (target)
	{
		setCell((Cell*)target);
		return MoveEffect::apply(dynamic_cast<SpellTarget*>(_caster));
	}
	return false;
}