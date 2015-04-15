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
	if (OverTimeEffect::newTurn())
	{
		if (_target)
		{
			_target->addBonusDamage(_amount);
			return true;
		}
			
	}
	return false;
}
