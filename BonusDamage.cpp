#include "BonusDamage.h"


BonusDamage::BonusDamage(int dmg, int duration, string name, SpellTarget *t)
	:DamageOverTime( dmg,  duration,  name, t)
{
}


BonusDamage::~BonusDamage()
{
}
