#include "AreaOfEffect.h"
#include "Cell.h"


AreaOfEffect::AreaOfEffect(string name)
	: _name(name)
{
}


AreaOfEffect::~AreaOfEffect()
{
}

void AreaOfEffect::addCell(Cell* c)
{
	if (c)
		_cells.push_back(c);
}
void AreaOfEffect::displayBasic(ostream& o) const
{
	o << _name;
}
void AreaOfEffect::lowerHitPoint(int amount)
{
	/* there should be no null value in the list */
	for (Cell* c : _cells)
	{
		c->lowerHitPoint(amount);
	}
}
void AreaOfEffect::removeMovementPoint(int amount)
{
	for (Cell* c : _cells)
	{
		c->removeMovementPoint(amount);
	}
}
void AreaOfEffect::removeCapaciyPoint(int amount)
{
	for (Cell* c : _cells)
	{
		c->removeCapaciyPoint(amount);
	}
}