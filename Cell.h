#pragma once
class Cell
{
public:
	typedef enum _STATE {
		Free, PlayerOnIt, Obstacle
	};
	Cell(int x=0, int y=0);
	~Cell();

	void setType(_STATE t);
	int getPosX() const;
	int getPosY() const;
	int getDistance(const Cell & c) const;

private:
	_STATE _cellType;
	int _posX;
	int _posY;
};

