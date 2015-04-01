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

	virtual void displayBasic(ostream& o) const = 0;
	virtual Cell* getCell() const = 0;
	virtual int getDistance(const SpellTarget& st) const = 0;

	virtual void lowerHitPoint(int amount) = 0;
	
	virtual void addEffect(OverTimeEffect*) = 0;
	
};


