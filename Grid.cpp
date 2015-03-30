#include "Grid.h"


Grid::Grid()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
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
		int y = rand() % HEIGHT;
		arrayOfCells[x][y].setType(Cell::Obstacle);
	}
}

void Grid::display(ostream& o) const
{
	for (auto &a : arrayOfCells)
	{
		for (const Cell &c : a)
		{
			if (c.getType() != Cell::Free)
				o << c << endl;
		}
	}
}

void Grid::setObject(GameObject* go, int i, int j)
{
	if (i < Grid::WIDTH && j < Grid::HEIGHT)
	{
		arrayOfCells[i][j].setObject(go);
	}
}

Cell* Grid::getCellAt(int i, int j)
{
	if (i>WIDTH || j>HEIGHT || i < 0 || j < 0)
	{
		LOGERR << "Index de getCellAt() hors de la grille !" << endl;
		return nullptr;
	}
	return &arrayOfCells[i][j];
}

int Grid::getCellDistance(int i, int j, int x, int y)
{
	int ret = getCellDistance(arrayOfCells[i][j], arrayOfCells[x][y]);
	return ret;
}

int Grid::getCellDistance(const Cell& c1, const Cell& c2)
{
	int ret = c1.getDistance(c2);
	return ret;
}