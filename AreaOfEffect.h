#pragma once
#include <string>
#include <list>
#include "SpellTarget.h"
#include "Grid.h"
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
	virtual void heal(int amount);
	virtual void removeMovementPoint(int amount);
	virtual void removeCapaciyPoint(int amount);
	virtual void addEffect(OverTimeEffect*);
	virtual void addBonusDamage(int amount);
	virtual void root();
	virtual bool move(int i, int j, bool moveWanted=true);
	virtual bool move(Cell & newCell, bool moveWanted=true);

protected:
	string _name;
	list<Cell*> _cells;
};

