#pragma once
#include "GameObject.h"

class Character;

class Cell
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
	int getDistance(const Character & c) const;
	bool isInView(const Cell & c) const;
	bool isInView(const Character & c) const;

	GameObject* getObject() const { return _object; }
	void setObject(GameObject* obj) throw( const char*)
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

