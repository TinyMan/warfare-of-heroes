#include "Character.h"
#include "Cell.h"
#include "Grid.h"
#include "Spell.h"


Character::Character(int x, int y, string name) : _name(name), _spells(NB_SPELLS)
{
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

void Character::setDot(DamageOverTime* dot)
{
	_damageOverTime.push_back(dot);
	LOGINFO << this->getName() << " : take DoT = " << dot << endl;
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

bool Character::move(Cell& c, bool moveWanted)
{
	LOGINFO << _name << " is moving from " << *_hisCell << " to " << c << endl;
	try
	{
		int distance = GAMEINST->getGrid()->getCellDistance(c, *_hisCell);
		if (distance > _movementPoints && moveWanted) throw "not enough movement points";
		c.setObject(this);
		_hisCell->setType(Cell::Free);
		_hisCell = &c;
		if (moveWanted)
			_movementPoints -= distance;	
	}
	catch (const char * msg)
	{
		LOGERR << "Cannot move : " << msg << endl;
		return false;
	}
	return true;
}
bool Character::move(int i, int j, bool moveWanted)
{
	// TO DO: over load to take Cell in parameter
	Cell* cell = GAMEINST->getGrid()->getCellAt(i, j);
	if (cell != nullptr)		
			return move(*cell,moveWanted);

	return false;
}

void Character::beginTurn()
{
	/* add actions to the 'menu' */
	UI->addAction(Action(Callback(&Character::targetSelectorForCell, this, ACTION_MOVE), "Move"));
		
	UI->addAction(Action(Callback(&Character::targetSelectorForCharacter, this, Character::BASIC_ATTACK), "Basic attack"));
	/* casting a spell isn't handled by character but by each class (archer, knight, ..) */
	//UI->addAction(Action(Callback(&Character::actionCallback, this, ACTION_CAST), "Cast a spell"));




	/*if (_damageOverTime > 0)
	{
		LOGINFO << this->getName() << " : taking damages (DoT) : " << _damageOverTime << endl;
		this->lowerHitPoint(_damageOverTime);
	}*/
	_capacityPoints = cpMax;
	_movementPoints = mpMax;
}

void Character::actionCallback(int actionID, void* d)
{
	switch (actionID)
	{
	case ACTION_MOVE:
		// TO DO: get a cell from the askWhereToMove and then move to the cell using move()
		move(*(Cell*)d);
		break;
	case ACTION_ENDTURN:
		GAMEINST->endTurn();
		break;
	default:
		cast(actionID, d);
		break;
	}
}

void Character::targetSelectorForCell(int spellID, void* d)
{
	// TO DO: changes to return a cell
	int x, y;
	LOGINFO << "Enter cell position (e.g. 13 29): " << endl;
	cin >> x >> y;
	try{
		Cell* c = GAMEINST->getGrid()->getCellAt(x, y);
		if (c == nullptr) throw std::out_of_range("cell does not exists");
		actionCallback(spellID, c);
	}
	catch (const std::out_of_range& oor) {
		LOGERR << "Out of Range error: " << oor.what() << " (cell does not exists)\n";
	}
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

int Character::getDistance(const SpellTarget& st) const
{
	return Grid::getCellDistance(*_hisCell, *st.getCell());
}
void Character::displayBasic(ostream& o) const
{
	o << _name;
}

SpellTarget* Character::targetSelector()
{
	LOGINFO << "Select your target: " << endl;
	GAMEINST->displayPlayersList(LOGINFO);
	int c;
	cin >> c;
	try{
		Character *target = GAMEINST->getPlayer(c);
		return target;
	}
	catch (const std::out_of_range& oor) {
		LOGERR << "Out of Range error: " << oor.what() << " (player does not exists)\n";
	}
	return nullptr;
}
ostream& operator<<(ostream& o, const Character& c)
{
	o << "Displaying: " << c._name << endl;
	o << "|-- Position: " << c._hisCell->getPosX() << "," << c._hisCell->getPosY() << endl;
	//o << "Stats: " << endl;
	o << "|-- HP: " << c._hitPoints << "/" << c.hpMax << endl;
	o << "|-- MP: " << c._movementPoints << endl;
	o << "|-- CP: " << c._capacityPoints << endl;
	//o << "|-- DoT: " << c._damageOverTime << endl;

	return o;
}

