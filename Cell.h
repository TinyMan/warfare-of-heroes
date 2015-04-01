#pragma once
#include "GameObject.h"
#include "SpellTarget.h"

class Character;

class Cell
	: public SpellTarget
{
public:
	typedef enum _STATE {
		Free, PlayerOnIt, Obstacle
	};
	Cell(int x=0, int y=0);
	~Cell();

	/* getters */
	_STATE getType() const { return _cellType; }
	int getPosX() const { return _posX; }
	int getPosY() const { return _posY;	}
	int getDistance(const Cell & c) const;
	int getDistance(const SpellTarget& st) const;
	const Cell* getCell() const { return this; }
	SpellTarget* getObject() const { return _object; }
	void displayBasic(ostream& o) const;

	bool isInView(const Cell & c) const;
	bool isInView(const SpellTarget & c) const;
	bool isInLine(const Cell& c) const;

	/* setters */
	void setObject(SpellTarget* obj);
	void setType(_STATE t);
	void lowerHitPoint(int amount) { _object->lowerHitPoint(amount); }
	void removeMovementPoint(int amount) { _object->removeMovementPoint(amount); }
	void removeCapaciyPoint(int amount) { _object->removeCapaciyPoint(amount); }
	void addEffect(OverTimeEffect* d) { _object->addEffect(d); }
	void addBonusDamage(int amount) { _object->addBonusDamage(amount); }
	void root() { _object->root(); }
	bool move(int i, int j, bool moveWanted) { return _object->move(i, j, moveWanted); }
	bool move(Cell & newCell, bool moveWanted) { return _object->move(newCell, moveWanted); }


	friend ostream& operator<<(ostream&, const Cell&);
private:
	_STATE _cellType;
	int _posX;
	int _posY;

	SpellTarget* _object = nullptr;
};

