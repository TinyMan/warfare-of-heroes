#pragma once
#include <iostream>

using namespace std;
class Cell;
class DamageOverTime;

/*  *interface* that (for example) Character and Cell should implement as they are targetable with spell*/
class SpellTarget
{
public:
	SpellTarget();
	virtual ~SpellTarget();

	virtual void displayBasic(ostream& o) const = 0;
	virtual Cell* getCell() const = 0;
	virtual int getDistance(const SpellTarget& st) const = 0;

	virtual void lowerHitPoint(int amount) = 0;
	virtual void setDot(DamageOverTime* dot) = 0;
	
};


