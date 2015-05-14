#pragma once
#include <list>
#include "GameObject.h"
#include "SpellTarget.h"
#include "OverTimeEffect.h"


class Cell
	: public SpellTarget
{
public:
	typedef enum _STATE {
		Free, PlayerOnIt, Obstacle
	};
	Cell(unsigned int number = 0, int x = 0, int y = 0);
	~Cell();

	/* getters */
	_STATE getType() const { return _cellType; }
	int getPosX() const { return _posX; }
	int getPosY() const { return _posY;	}
	unsigned int getNumber() const { return _number; }
	int getDistance(const Cell & c) const;
	const Cell* getCell() const { return this; }
	SpellTarget* getObject() const { return _object; }
	void displayBasic(ostream& o) const;
	bool hisTurn() const { if (_object) return _object->hisTurn(); else return false; }


	bool isInView(const Cell & c) const;
	bool isInView(const SpellTarget & c) const;
	bool isInLine(const Cell& c) const;

	/* setters */
	void setObject(SpellTarget* obj);
	void free();
	void setType(_STATE t);
	void lowerHitPoint(int amount) { if(_object) _object->lowerHitPoint(amount); }
	void heal(int amount) { if (_object) _object->heal(amount); }
	void removeMovementPoint(int amount) { if (_object)_object->removeMovementPoint(amount); }
	void removeCapaciyPoint(int amount) { if (_object)_object->removeCapaciyPoint(amount); }
	void addEffect(OverTimeEffect* d);
	void addBonusDamage(int amount) { if (_object)_object->addBonusDamage(amount); }
	void root() { if (_object) _object->root(); }
	bool move(int i, int j, bool moveWanted) { if (_object)return _object->move(i, j, moveWanted); else return false; }
	bool move(Cell & newCell, bool moveWanted) { if (_object) return _object->move(newCell, moveWanted); else return false; }
	
	virtual void beginTurn();

	friend ostream& operator<<(ostream&, const Cell&);
private:
	_STATE _cellType;
	int _posX;
	int _posY;
	unsigned int _number;

	SpellTarget* _object = nullptr;
	list<OverTimeEffect*> _effects;
};

