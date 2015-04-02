#include "SquareAoE.h"
#include "Cell.h"
#include "Game.h"


SquareAoE::SquareAoE(const Cell* center, int len)
	: _len(len), _center(center)
{
	extrapole();
}


SquareAoE::~SquareAoE()
{
}

void SquareAoE::setCenter(Cell* center)
{
	_center = center;
	extrapole();
}
void SquareAoE::setLen(int len)
{
	_len = len;
	extrapole();
}
void SquareAoE::extrapole()
{
	if (_center && _len > 0)
	{
		for (int i = -_len / 2; i < _center->getPosX() + _len / 2; i++)
		{
			for (int j = -_len / 2; j < _center->getPosY() + _len / 2; j++)
			{
				addCell(GAMEINST->getGrid()->getCellAt(_center->getPosX() + i, _center->getPosY() + j));
			}
		}
	}
}
void SquareAoE::displayBasic(ostream& o) const
{
	o << _name << " (center: " ;
	if (_center)
		_center->displayBasic(o);
	else
		o << "not set";
	o << ")";
}
