#include "LineAoE.h"
#include "Cell.h"
#include "Game.h"



LineAoE::LineAoE(const Cell* first, const Cell* last)
	: AreaOfEffect("Line AoE"), _first(first), _last(last)
{
	extrapole();
}

LineAoE::LineAoE(const Cell* first, const Cell* second, int range)
	: AreaOfEffect("Line AoE"), _first(first)
{
	if (first == second) throw("First cell and Second cell should not be the same !");
	Grid * grid = GAMEINST->getGrid();
	Grid::DIRECTION d = grid->getDir(*first, *second);

	_last = grid->getCellFromCellAndDir(*first, d, range - 1);
	/*
	LOGINFO << "Constructing new LineAoE:" << endl;
	LOGINFO << "|-- First: " << *first << endl;
	LOGINFO << "|-- Second: " << *second << endl;
	LOGINFO << "|-- Range: " << range << endl;
	LOGINFO << "|-- Last: " << *_last << endl;*/
	extrapole();
}
LineAoE::LineAoE(const Cell* first, Grid::DIRECTION direction, int range)
	: AreaOfEffect("Line AoE"), _first(first)
{
	if (direction == Grid::UNKNOWN) throw("Unknown direction");
	_last = GAMEINST->getGrid()->getCellFromCellAndDir(*first, direction, range - 1);
	extrapole();
}


LineAoE::~LineAoE()
{
}

void LineAoE::extrapole()
{
	if (_first)
	{
		if (_last && _first->isInLine(*_last))
		{
			Grid* grid = GAMEINST->getGrid();
			int i = _first->getPosX();
			int j = _first->getPosY();
			if (_last->getPosX() != i)
			{
				int minI = min(i, _last->getPosX());
				int maxI = max(i, _last->getPosX());
				for (i = minI; i <= maxI; i++)
				{
					Cell* cell = grid->getCellAt(i, j);
					addCell(cell);
				}
			}
			else
			{
				int minJ = min(j, _last->getPosY());
				int maxJ = max(j, _last->getPosY());
				for (j = minJ; j <= maxJ; j++)
				{
					Cell* cell = grid->getCellAt(i, j);
					addCell(cell);
				}
			}
		}
	}
}
ostream& operator<<(ostream& o, const LineAoE& l)
{
	o << "Displaying " << l._name << ":" << endl;
	o << "|-- First cell: " << *l._first << endl;
	o << "|-- Last cell: " << *l._last << endl;

	return o;
}