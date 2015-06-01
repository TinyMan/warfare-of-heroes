#include "Activable.h"


Activable::Activable()
{
}


Activable::~Activable()
{
}

void Activable::setActive(bool b, void*)
{ 
	if (_active != b)
	{
		_active = b;
		setDirty();
	}
}
bool Activable::operator<(const Activable& o)
{
	if (o.isActive() == isActive())
		return false;
	return o.isActive() && !isActive();
}