#include "DamageBuffEffect.h"
#include "SpellTarget.h"


DamageBuffEffect::DamageBuffEffect(int amount, int duration, Character* caster)
	: OverTimeEffect(duration, "Damage Buff", caster), _amount(amount)
{	
}


DamageBuffEffect::~DamageBuffEffect()
{
}

bool DamageBuffEffect::beginTurn()
{
	if (OverTimeEffect::_target)
	{
		OverTimeEffect::_target->addBonusDamage(_amount);
		return true;
	}
	return false;
}
