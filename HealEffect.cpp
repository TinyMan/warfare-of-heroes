#include "HealEffect.h"
#include "SpellTarget.h"
#include "Character.h"


HealEffect::HealEffect(int heal, Character* st)
	: Effect("Heal Effect", st), _heal(heal)
{
}


HealEffect::~HealEffect()
{
}
bool HealEffect::apply(SpellTarget* st)
{
	if (st)
	{		
		st->lowerHitPoint(-_heal);
		return true;
	}
	return false;
}
