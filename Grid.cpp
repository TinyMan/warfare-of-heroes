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

void Grid::generateObstacle() {
	for (int i = 0; i < 4; i++)
	{
		int x = rand() % WIDTH;
		int y = rand() % LENGTH;
		arrayOfCells[x][y].setType(Cell::Obstacle);
	}
}
