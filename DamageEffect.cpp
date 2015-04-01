#include "DamageEffect.h"
#include "SpellTarget.h"


DamageEffect::DamageEffect(int dmg, SpellTarget* st)
	: Effect( "Damage effect", st), _damage(dmg)
{
}


DamageEffect::~DamageEffect()
{
}
bool DamageEffect::apply(SpellTarget* st)
{
	if (st == nullptr)
		st = _target;

	if (st)
	{
		st->lowerHitPoint(_damage);
		return true;
	}
	return false;
}
