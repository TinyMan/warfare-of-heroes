#include "OverTimeEffect.h"
#include "SpellTarget.h"


OverTimeEffect::OverTimeEffect(int duration, string name, Character* t)
	: _max_duration(duration), _duration(duration), Effect(name, t)
{
}


OverTimeEffect::~OverTimeEffect()
{
}
bool OverTimeEffect::newTurn()
{
	_to_delete = (--_duration < 0);
	return !_to_delete;
}

bool OverTimeEffect::apply(SpellTarget *target)
{
	if (!_target)
	{		
		_target = target;
	}
	_target->addEffect(this);
	return true;
}