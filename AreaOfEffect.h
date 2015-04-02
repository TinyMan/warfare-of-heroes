#pragma once
#include <string>
#include <list>
#include "SpellTarget.h"
class Cell;

using namespace std;

class AreaOfEffect :
	public SpellTarget
{
public:
	AreaOfEffect(string name="Unknown AoE");
	virtual ~AreaOfEffect();

	list<Cell*> getCells() const { return _cells; }
	void addCell(Cell* c);

	/* getters */
	virtual void displayBasic(ostream& o) const;
	virtual bool hisTurn() const { return true; }

	/* setters */
	virtual void lowerHitPoint(int amount);
	virtual void removeMovementPoint(int amount);
	virtual void removeCapaciyPoint(int amount);
	virtual void addEffect(OverTimeEffect*) = 0;
	virtual void addBonusDamage(int amount) = 0;
	virtual void root() = 0;
	virtual bool move(int i, int j, bool moveWanted) = 0;
	virtual bool move(Cell & newCell, bool moveWanted) = 0;

protected:
	string _name;
	list<Cell*> _cells;
};

