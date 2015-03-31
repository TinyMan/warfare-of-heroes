#pragma once
#include <iostream>
#include "Cell.h"

using namespace std;

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
	
};


