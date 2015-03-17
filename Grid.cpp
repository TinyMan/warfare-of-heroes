#include "Grid.h"


Grid::Grid()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < LENGTH; j++)
		{
			arrayOfCells[i][j] = Cell(i, j);
		}
	}
}


Grid::~Grid()
{
}
