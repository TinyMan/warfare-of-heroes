#include "RootEffect.h"
#include "SpellTarget.h"

RootEffect::RootEffect(int duration, Character* caster)
	: OverTimeEffect(duration, "Root Effect", caster)
{
}


RootEffect::~RootEffect()
{
}

bool RootEffect::beginTurn()
{
	if (OverTimeEffect::newTurn() && _target)
	{
		_target->root();
	}
	return false;
}
