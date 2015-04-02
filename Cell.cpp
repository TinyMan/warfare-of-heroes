#include "Cell.h"
#include "Character.h"

Cell::Cell(int x, int y)
{
	_posX = x;
	_posY = y;
	_cellType = Free;
}


Cell::~Cell()
{
}

void Cell::setType(_STATE t)
{
	_cellType = t;
}
void Cell::setObject(SpellTarget* obj)
{
	if (_cellType != Free)
		throw "Cannot set object: Cell is not free";
	_cellType = PlayerOnIt;
	_object = obj;
	/* TODO: CHANGE TYPE OF CELL */
}
void Cell::addEffect(OverTimeEffect* e)
{
	e->setTarget(this);
	_effects.push_back(e);
	LOGINFO << "Adding over time effect " << *e << " to " << *this << endl;
}
int Cell::getDistance(const Cell & c) const
// Returns the distance between the object and the cell given as parameter
{
	int X1 = c.getPosX();
	int Y1 = c.getPosY();
	int X2 = getPosX();
	int Y2 = getPosY();

	int temp,distance;
	if (X1 > X2)
	{
		temp = X2;
		X2 = X1;
		X1 = temp;
	}
	if (Y1 > Y2)
	{
		temp = Y2;
		Y2 = Y1;
		Y1 = temp;
	}

	distance = (Y2 - Y1) + (X2 - X1);
	return distance;
}

bool Cell::isInView(const Cell & c) const
{
	// TODO : vérifier la ligne de vue (obstacle ou non)
	return true;
}

bool Cell::isInView(const SpellTarget & c) const
{
	Cell hisCell = *c.getCell();
	return (isInView(hisCell));
}

bool Cell::isInLine(const Cell& c) const
{
	return c._posX == _posX || c._posY == _posY;
}

void Cell::beginTurn()
{
	for (auto e : _effects)
	{
		e->beginTurn();
	}
}
void Cell::displayBasic(ostream& o) const
{
	o << *this;
}
ostream& operator<<(ostream& o, const Cell& c)
{
	o << "Cell " << c._posX << "," << c._posY << ": ";
	switch (c._cellType)
	{
	case Cell::Free:
		o << "Free";
		break;
	case Cell::Obstacle:
		o << "Obstacle";
		break;
	case Cell::PlayerOnIt:
		o << "Player";
		break;
	default:
		break;
	}
	return o;
}