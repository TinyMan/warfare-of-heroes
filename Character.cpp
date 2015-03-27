#include "Character.h"
#include "Cell.h"
#include "Grid.h"


Character::Character(int x, int y, string name)
{
	_name = name;
	Grid* grid = Game::getInstance()->getGrid();
	grid->setObject(this, x, y);
	_hisCell = grid->getCellAt(x, y);
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

bool Character::movement()
{
	// Bla bla bla I move hourray !
	// Launches a super duper animation.
	return true;
}

bool Character::move(int i, int j)
{
	// TO DO: over load to take Cell in parameter
	LOGINFO << _name << " is moving from " << *_hisCell << " to " << i << ", " << j << endl;
	int distance = Grid::getCellDistance(i, j, _hisCell->getPosX(), _hisCell->getPosY());
	if (distance <= _movementPoints)
	{
		_hisCell = GAMEINST->getGrid()->getCellAt(i, j);
		if (_hisCell != nullptr)
		{
			_movementPoints -= distance;
			return true;
		}
	}
	else
		LOGERR << "Cannot move: not enough movement points" << endl;
	return false;
}

void Character::beginTurn()
{
	/* add actions to the 'menu' */
	UI->addAction(Action(Callback(&Character::actionCallback, this, ACTION_MOVE), "Move"));
		
	UI->addAction(Action(Callback(&Character::targetSelectorForCharacter, this, Character::BASIC_ATTACK), "Basic attack"));
	/* casting a spell isn't handled by character but by each class (archer, knight, ..) */
	//UI->addAction(Action(Callback(&Character::actionCallback, this, ACTION_CAST), "Cast a spell"));
}

void Character::actionCallback(int actionID, void* d)
{
	switch (actionID)
	{
	case ACTION_MOVE:
		// TO DO: get a cell from the askWhereToMove and then move to the cell using move()
		askWhereToMove(d);
		break;
	case ACTION_CAST:
		break;
	case ACTION_ENDTURN:
		GAMEINST->endTurn();
		break;
	default:
		break;
	}
}

void Character::askWhereToMove(void*)
{
	// TO DO: changes to return a cell
	int x, y;
	LOGINFO << "Where do you want to go ? Enter cell position (e.g. 13 29): " << endl;
	cin >> x >> y;
	move(x, y);
}
void Character::targetSelectorForCharacter(int spellIID, void* d)
{
	LOGINFO << "Select your target: " << endl;
	GAMEINST->displayPlayersList(LOGINFO);
	int c;
	cin >> c;
	try{
		Character *target = GAMEINST->getPlayer(c);
		cast(spellIID, target);
	}
	catch (const std::out_of_range& oor) {
		LOGERR << "Out of Range error: " << oor.what() << " (player does not exists)\n";
	}
}

ostream& operator<<(ostream& o, const Character& c)
{
	o << "Displaying: " << c._name << endl;
	o << "Position: " << c._hisCell->getPosX() << "," << c._hisCell->getPosY() << endl;
	return o;
}

