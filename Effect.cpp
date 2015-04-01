#include "Effect.h"


Effect::Effect(string name, Character* st)
	: _caster(st), _name(name)
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