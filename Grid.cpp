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

void Grid::setObject(SpellTarget* go, int i, int j)
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

Cell* Grid::getCellFromCellAndDir(const Cell& c, DIRECTION d, int pathLen)
{
	int i = c.getPosX();
	int j = c.getPosY();
	switch (d)
	{
	case Grid::TOP:
		j -= pathLen;
		break;
	case Grid::BOTTOM:
		j += pathLen;
		break;
	case Grid::RIGHT:
		i += pathLen;
		break;
	case Grid::LEFT:
		i -= pathLen;
		break;
	default:
		break;
	}
	return getCellAt(i, j);
}
Grid::DIRECTION Grid::getDir(const Cell& c1, const Cell& c2)
{
	DIRECTION d = UNKNOWN;
	if (c1.getPosX() == c2.getPosX())
	{
		if (c1.getPosY() < c2.getPosY())
		{
			d = BOTTOM;
		}
		else
			d = TOP;
	}
	else if (c1.getPosY() == c2.getPosY())
	{
		if (c1.getPosX() < c2.getPosX())
		{
			d = RIGHT;
		}
		else
			d = LEFT;
	}
		
	return d;
}

void Grid::beginTurn()
{
	for (auto& l : arrayOfCells)
	{
		for (Cell& c : l)
		{
			c.beginTurn();
		}
	}
}