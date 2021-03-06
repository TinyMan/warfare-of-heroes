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
	int getDistance(const SpellTarget& st) const;

	/* getters */
	virtual void displayBasic(ostream& o) const =0;
	virtual const Cell* getCell() const = 0;
	virtual bool hisTurn() const = 0;
	virtual list<Cell*> getCells() const { list<Cell*> ret; ret.push_back((Cell*)getCell()); return ret; }
	virtual list<OverTimeEffect*> getEffects() const { return _effects; }
	virtual bool hasEffect(string name) const;

	/* setters */
	virtual void lowerHitPoint(int amount) = 0;
	virtual void heal(int amount) = 0;
	virtual void removeMovementPoint(int amount) =0;
	virtual void removeCapaciyPoint(int amount) =0;
	virtual void addEffect(OverTimeEffect*) =0;
	virtual void addBonusDamage(int amount) =0;
	virtual void root() =0;
	virtual bool move(int i, int j, bool moveWanted) =0;
	virtual bool move(Cell & newCell, bool moveWanted) = 0;

protected:
	list<OverTimeEffect*> _effects;
	
};


