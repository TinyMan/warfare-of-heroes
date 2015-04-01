#include "DamageOverTime.h"
#include "SpellTarget.h"


DamageOverTime::DamageOverTime(int dmg, int duration, string name, Character *t)
	: _damage(dmg), OverTimeEffect(duration, name, t)
{
}


DamageOverTime::~DamageOverTime()
{
}

bool DamageOverTime::beginTurn()
{
	if (OverTimeEffect::newTurn())
	{	
		if (_target)
		{
			_target->lowerHitPoint(_damage);
			return true;
		}
	}
	return false;
}

ostream& operator<<(ostream& o, const DamageOverTime& dot)
{
	o << dot._name << ": " << dot._damage << " (" << dot._duration << " turn left)" << endl;
	return o;
}