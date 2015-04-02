#pragma once
#include "AreaOfEffect.h"
class SquareAoE :
	public AreaOfEffect
{
public:
	SquareAoE(Cell* center = nullptr, int len = 0);

	virtual ~SquareAoE();

	void setCenter(Cell* c);
	void setLen(int len);

	void extrapole();

	/* getters */
	virtual void displayBasic(ostream& o) const;
	virtual const Cell* getCell() const { return _center; }
	virtual int getDistance(const SpellTarget& st) const { return 0; }
	virtual bool hisTurn() const { return true; }

	/* setters */
	virtual void lowerHitPoint(int amount) = 0;
	virtual void removeMovementPoint(int amount) = 0;
	virtual void removeCapaciyPoint(int amount) = 0;
	virtual void addEffect(OverTimeEffect*) = 0;
	virtual void addBonusDamage(int amount) = 0;
	virtual void root() = 0;
	virtual bool move(int i, int j, bool moveWanted) = 0;
	virtual bool move(Cell & newCell, bool moveWanted) = 0;
protected:
	Cell* _center;
	int _len;
};

