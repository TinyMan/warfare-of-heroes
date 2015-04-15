#include "DiamondAoE.h"
#include "Game.h"
#include "Cell.h"


DiamondAoE::DiamondAoE(const Cell* center, int len)
	: SquareAoE(center)
{
	setLen(len);
}


DiamondAoE::~DiamondAoE()
{
}


void DiamondAoE::extrapole()
{
	if (_center && _len > 0)
	{
		int centerX = _center->getPosX();
		int centerY = _center->getPosY();
		for (int i = centerX - _len; i <= centerX + _len; i++)
		{
			for (int j = centerY - _len; j <= centerY + _len; j++)
			{
				Cell* cell = GAMEINST->getGrid()->getCellAt(i, j);
				if (cell)
					if (_center->getDistance(*cell) <= _len)
						addCell(cell);
			}
		}
		/*for (int i = -_len / 2 + 1; i < _center->getPosX() + _len / 2 + 1; i++)
		{
			for (int j = -_len / 2 + 1; j < _center->getPosY() + _len / 2 + 1; j++)
			{
				Cell* cell = GAMEINST->getGrid()->getCellAt(_center->getPosX() + i, _center->getPosY() + j);
				if (cell)
					if(_center->getDistance(*cell) <= _len)
						addCell(cell);
			}
		}*/
	}
}
