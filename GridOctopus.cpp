#include "GridOctopus.h"


GridOctopus::GridOctopus(Grid* g)
	: Panel(Grid::WIDTH * 50, Grid::HEIGHT/2 * 25), _grid(g)
{
	setBgColor(Color::TRANSPARENT);
	double x = 0, y = 0;
	for (size_t j = 0; j < Grid::HEIGHT; j++)
	{
		for (size_t i = 0; i < Grid::WIDTH; i++)
		{
			_cells[i][j] = new CellOctopus(_grid->getCellAt(i, j));
			add(_cells[i][j], int(x * 50), int(y * 25));

			x++;
			if (x == 14)
			{
				x = 0.5;
				y += 0.5;
			}
			else if (x == 14.5)
			{
				x = 0;
				y += 0.5;
			}
		}
	}
}


GridOctopus::~GridOctopus()
{
}

CellOctopus* GridOctopus::getCellOctopus(const Cell* c) const
{
	bool found = false;
	size_t i = 0;
	size_t j;
	while (!found && i < Grid::WIDTH)
	{
		j = 0;
		while (!found && j < Grid::HEIGHT)
		{
			found = _cells[i][j]->getCell() == c;
			j++;
		}
		i++;
	}
	if (found)
		return _cells[--i][--j];
	else
		return nullptr;
}