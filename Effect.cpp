#include "Effect.h"


Effect::Effect(string name, SpellTarget* st)
	: _target(st), _name(name)
{
}


Effect::~Effect()
{
}
