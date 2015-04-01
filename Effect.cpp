#include "Effect.h"


Effect::Effect(string name, SpellTarget* st)
	: _target(st), _name(name)
{
}


Effect::~Effect()
{
}

ostream& operator<<(ostream& o, const Effect& effect)
{
	o << effect._name;
	return o;
}