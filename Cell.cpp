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
