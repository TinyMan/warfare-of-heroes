#include "DamageOverTime.h"


DamageOverTime::DamageOverTime(int dmg, int duration, string name, SpellTarget *t)
	: _target(t), _damage(dmg), _duration(duration), _name(name)
{
}


DamageOverTime::~DamageOverTime()
{
}

void DamageOverTime::beginTurn()
{
	if (_duration-- > 0)
		_target->lowerHitPoint(_damage);
	else
		_to_delete = true;
}

ostream& operator<<(ostream& o, const DamageOverTime& dot)
{
	o << dot._name << ": " << dot._damage << " (" << dot._duration << " turn left)" << endl;
	return o;
}