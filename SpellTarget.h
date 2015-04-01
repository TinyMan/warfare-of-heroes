#pragma once
#include <iostream>
#include "ServiceLocator.h"

using namespace std;
class Cell;
class DamageOverTime;
class BonusDamage;
class OverTimeEffect;

/*  *interface* that (for example) Character and Cell should implement as they are targetable with spell*/
class SpellTarget
{
public:
	SpellTarget();
	virtual ~SpellTarget();

	virtual void displayBasic(ostream& o) const {};
	virtual const Cell* getCell() const = 0;
	virtual int getDistance(const SpellTarget& st) const = 0;

	/* setters */
	// TO DO soon it will be pure virtual (need to implement these in cell)
	virtual void lowerHitPoint(int amount) {};
	virtual void removeMovementPoint(int amount) {};
	virtual void removeCapaciyPoint(int amount) {};
	virtual void addEffect(OverTimeEffect*) {};
	virtual void addBonusDamage(int amount) {};
	virtual void root() {};
	virtual bool move(int i, int j, bool moveWanted) { return false; };
	virtual bool move(Cell & newCell, bool moveWanted) { return false; };

	
};


