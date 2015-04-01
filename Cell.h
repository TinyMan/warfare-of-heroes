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

	void setType(_STATE t);
	_STATE getType() const { return _cellType; }
	int getPosX() const { return _posX; }
	int getPosY() const { return _posY;	}
	int getDistance(const Cell & c) const;
	int getDistance(const SpellTarget& st) const;
	const Cell* getCell() const { return this; }

	bool isInView(const Cell & c) const;
	bool isInView(const SpellTarget & c) const;
	bool isInLine(const Cell& c) const;

	GameObject* getObject() const { return _object; }
	void setObject(GameObject* obj)
	{ 
		_object = obj; 
		if (_cellType != Free) 
			throw "Cannot set object: Cell is not free";
		_cellType = PlayerOnIt;
		/* TODO: CHANGE TYPE OF CELL */ 
	}

	friend ostream& operator<<(ostream&, const Cell&);
private:
	_STATE _cellType;
	int _posX;
	int _posY;

	GameObject* _object = nullptr;
};

