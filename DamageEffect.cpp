#include "DamageEffect.h"
#include "SpellTarget.h"
#include "Character.h"


DamageEffect::DamageEffect(int dmg, Character* st)
	: Effect( "Damage effect", st), _damage(dmg)
{
}


DamageEffect::~DamageEffect()
{
}
bool DamageEffect::apply(SpellTarget* st)
{
	if (st)
	{
		int dmg = _damage;
		if (_caster)
			dmg += _caster->getBonusDamage();
		st->lowerHitPoint(dmg);
		return true;
	}
	return false;
}
