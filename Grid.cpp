#include "Grid.h"


Grid::Grid()
{
	unsigned int n = 0;
	int nextX = -13;
	int nextY = 0;
	for (int j = 0; j < Grid::HEIGHT * 2 - 1; ++j)
	{
		bool big = j % 2 == 0;
		int width = big ? Grid::WIDTH : Grid::WIDTH - 1;

		int y = nextY;
		int x = nextX;
		for (int i = 0; i < width; i++)
		{
			if (n >= 0 && n < CELLS_NUMBER)
			{
				_cells[n] = Cell(n, x, y);
				_cells_coordinates[x][y] = n;
			}
			x++;
			y--;
			n++;
		}
		if (big)
		{
			nextX++;
		}
		else
		{
			nextY++;
		}
	}

			/*int n = toCellNumber(i, j);
			if (n >= 0 && n < CELLS_NUMBER)
			{
				_cells[n] = Cell( n, i, j);
				_cells_coordinates[i][j] = n;
			}*/
}


Grid::~Grid()
{
}

void Grid::generateObstacle() {
	/*for (int i = 0; i < 4; i++)
	{
		int x = rand() % WIDTH;
		int y = rand() % HEIGHT;
		arrayOfCells[x][y].setType(Cell::Obstacle);
	}*/
}

void Grid::display(ostream& o) const
{
	for (auto &c : _cells)
	{
		if (c.second.getType() != Cell::Free)
			o << c.second << endl;
	}
}
void Grid::setObject(SpellTarget* go, unsigned int n)
{
	_cells.at(n).setObject(go);
}
void Grid::setObject(SpellTarget* go, int i, int j)
{
	if (validCoordinates(i, j))
	{
		setObject(go, toCellNumber(i, j));
	}
}

Cell* Grid::getCellAt(int i, int j)
{
	if (!validCoordinates(i, j))
	{
		LOGERR << "Index de getCellAt() hors de la grille !" << endl;
		return nullptr;
	}
	return getCell(toCellNumber(i, j));
}
Cell* Grid::getCell(unsigned int n)
{
	if (_cells.count(n) != 1)
	{
		LOGERR << "Trying to get cell " << n << " but it is non existant" << endl;
		return nullptr;
	}
	return &_cells.at(n);
}
int Grid::getCellDistance(unsigned int n, unsigned int n2)
{
	return getCellDistance(_cells.at(n), _cells.at(n2));
}
int Grid::getCellDistance(int i, int j, int x, int y)
{
	int ret = getCellDistance(toCellNumber(i,j), toCellNumber(x, y));
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
	for (auto& c : _cells)
	{
		c.second.beginTurn();
	}
	
}