#pragma once
#include "GameObject.h"

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

	GameObject* getObject() const { return _object; }
	void setObject(GameObject* obj) { _object = obj; /* TODO: CHANGE TYPE OF CELL */}

private:
	_STATE _cellType;
	int _posX;
	int _posY;

	GameObject* _object = nullptr;
};

