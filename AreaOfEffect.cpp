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
		LOGINFO << "Lowering HP on " << *c << endl;
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
void AreaOfEffect::addEffect(OverTimeEffect* e)
{
	for (Cell* c : _cells)
	{
		OverTimeEffect *effect = e->clone();
		c->addEffect(effect);
	}
}
void AreaOfEffect::addBonusDamage(int e)
{
	for (Cell* c : _cells)
	{
		c->addBonusDamage(e);
	}
}
void AreaOfEffect::root()
{
	for (Cell* c : _cells)
	{
		c->root();
	}
}
bool AreaOfEffect::move(int i, int j, bool moveWanted)
{
	for (Cell* c : _cells)
	{
		c->move(i, j, moveWanted);
	}
	return true;
}
bool AreaOfEffect::move(Cell & newCell, bool moveWanted)
{
	for (Cell* c : _cells)
	{
		c->move(newCell, moveWanted);
	}
	return true;
}