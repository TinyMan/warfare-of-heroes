#include "Cell.h"

Cell::Cell(int x, int y)
{
	_posX = x;
	_posY = y;
}


Cell::~Cell()
{
}

void Cell::setType(_STATE t)
{
	_cellType = t;
}

int Cell::getDistance(const Cell & c) const
// Returns the distance between the object and the cell given as parameter
{
	int X1 = c.getPosX();
	int Y1 = c.getPosY();
	int X2 = getPosX();
	int Y2 = getPosY();

	int temp,distance;
	if (X1 > X2)
	{
		temp = X2;
		X2 = X1;
		X1 = temp;
	}
	if (Y1 > Y2)
	{
		temp = Y2;
		Y2 = Y1;
		Y1 = temp;
	}

	distance = (Y2 - Y1) + (X2 - X1);
	return distance;
}

bool isInView(const Cell & c) const
{
	// TODO : vérifier la ligne de vue (obstacle ou non)
}
