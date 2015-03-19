#include "Character.h"
#include "Cell.h"
#include "Grid.h"


Character::Character(string name)
{
	_name = name;
}


Character::~Character()
{
}

void Character::lowerHitPoint(int amount)
{
	_hitPoints -= amount;
	if (_hitPoints < 0)
		_hitPoints = 0;

}

void Character::removeMovementPoint(int amount)
{
	_movementPoints -= amount;
	if (_movementPoints < 0)
		_movementPoints = 0;
}

void Character::removeCapaciyPoint(int amount)
{
	_capacityPoints -= amount;
	if (_capacityPoints < 0)
		_capacityPoints = 0;
}

int Character::getHP() const
{
	return(_hitPoints);
}

int Character::getMP() const
{
	return(_movementPoints);
}

int Character::getCP() const
{
	return(_capacityPoints);
}


bool Character::basicAttack(Character & c)
{// TODO
	return true;
}

bool Character::movement()
{
	// Bla bla bla I move hourray !
	// Launches a super duper animation.
	return true;
}

bool Character::move(int i, int j)
{
	int distance = Grid::getCellDistance(i, j, _hisCell->getPosX(), _hisCell->getPosY());
	if (distance <= _movementPoints)
	{
		_movementPoints -= distance;
		// TODO:: _hisCell = Game::getInstance()->getGrid()->getCellAt(i, j);
		return true;
	}
	return false;
}