#include "Character.h"


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

int Character::getHP()
{
	return(_hitPoints);
}

int Character::getMP()
{
	return(_movementPoints);
}

int Character::getCP()
{
	return(_capacityPoints);
}

bool Character::basicAttack(Character & c)
{
	return true;
}

bool Character::movement()
{
	// Bla bla bla I move hourray !
	// Launches a super duper animation.
	return true;
}