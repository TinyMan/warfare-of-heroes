#include "Grid.h"


Grid::Grid()
	: pathFinder(bind(&Grid::getAdjacentCells, this, placeholders::_1), [](Cell* c) { return c && c->getType() == Cell::Free; }, [=](Cell* c1, Cell* c2) {return (double)getCellDistance(*c1, *c2); })
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
}


Grid::~Grid()
{
}

void Grid::generateObstacle() {
	for (int i = 0; i < nbObstacles; i++)
	{
		unsigned int n = rand() % CELLS_NUMBER;
		_cells[n].setType(Cell::Obstacle);
		_obstacles.push_back(&_cells[n]);
	}
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
	//	LOGERR << "Index de getCellAt() hors de la grille !" << endl;
		return nullptr;
	}
	return getCell(toCellNumber(i, j));
}
Cell* Grid::getCell(unsigned int n)
{
	if (_cells.count(n) != 1)
	{
	//	LOGERR << "Trying to get cell " << n << " but it is non existant" << endl;
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
	Cell* cell = getCellAt(i, j);
	while (cell == nullptr)
	{
		switch (d)
		{
		case Grid::TOP:
			j += 1;
			break;
		case Grid::BOTTOM:
			j -= 1;
			break;
		case Grid::RIGHT:
			i -= 1;
			break;
		case Grid::LEFT:
			i += 1;
			break;
		default:
			break;
		}
		cell = getCellAt(i, j);
	}
	return cell;
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

list<Cell*> Grid::getAdjacentCells(Cell* c)
{
	list<Cell*> ret;
	
	if (c)
	{
		int x = c->getPosX();
		int y = c->getPosY();
		Cell * c;
		if (c = getCellAt(x + 1, y))
			ret.push_back(c);
		if (c = getCellAt(x - 1, y))
			ret.push_back(c);
		if (c = getCellAt(x, y + 1))
			ret.push_back(c);
		if (c = getCellAt(x, y - 1))
			ret.push_back(c);
	}
	return ret;
}