#include "GridOctopus.h"


GridOctopus::GridOctopus(Grid* g)
	: Panel(Grid::WIDTH * 50, Grid::HEIGHT/2 * 25), _grid(g)
{
	setBgColor(Color::TRANSPARENT);
	double x = 0, y = 0;
	for (auto & i : _cells)
	{
		for (auto& e : i)
		{
			e = new CellOctopus(nullptr);
			add(e, int(x * 50), int(y * 25));
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
