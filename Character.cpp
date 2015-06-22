#include "Character.h"
#include "Cell.h"
#include "Grid.h"
#include "Spell.h"
#include "MoveEffect.h"


Character::Character(int x, int y, string name) : _name(name)
{
	Grid* grid = Game::getInstance()->getGrid();
	grid->setObject(this, x, y);
	_hisCell = grid->getCellAt(x, y);
	
}


Character::~Character()
{

	for (auto& s : getSpells())
	{
		delete s.second;
	}
	_hisCell->free();
}

void Character::lowerHitPoint(int amount)
{
	if (!_dead)
	{
		/* trigger taking damage event */
		if (_hitPoints < amount)
		{
			_dead = true;
			_hitPoints = 0;
			(new DieEvent(this))->dispatch();
		}
		else
		{
			_hitPoints -= amount;
		}
		(new LoseHpEvent(this, amount))->dispatch();
	}
}

void Character::heal(int amount)
{
	if (!_dead)
	{
		/* trigger heal event */
		_hitPoints += amount;
	}
}

void Character::removeMovementPoint(int amount)
{
	/* trigger event remove mp */
	_movementPoints -= amount;
	if (_movementPoints < 0)
		_movementPoints = 0;
}

void Character::removeCapaciyPoint(int amount)
{
	/* trigger event remove cp */
	_capacityPoints -= amount;
	if (_capacityPoints < 0)
		_capacityPoints = 0;
	(new LoseCPEvent(this, amount))->dispatch();
}
void Character::addBonusDamage(int amount)
{
	_bonusDamage += amount;
}
void Character::addEffect(OverTimeEffect* e)
{
	/* trigger event adding an effect */
	_effects.push_back(e);
	LOGINFO << "Adding over time effect " << *e << " to ";
	displayBasic(LOGINFO);
	LOGINFO << endl;
}
void Character::root()
{
	_movementPoints = 0;
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

bool Character::moveSingle(Cell& c, bool moveWanted)
{
	int distance = GAMEINST->getGrid()->getCellDistance(c, *_hisCell);
	if (distance > 1)
		throw "Cheat error";
	else if (distance > _movementPoints && moveWanted)
		throw "not enough movement point";

	(new MoveEvent(this, _hisCell, &c, moveWanted))->dispatch();
	_hisCell->free();
	c.setObject(this);
	_hisCell->setType(Cell::Free);
	_hisCell = &c;

	if (moveWanted)
		_movementPoints -= distance;

	return true;
}
bool Character::move(Cell& c, bool moveWanted)
{
	//LOGINFO << _name << " is moving from " << *_hisCell << " to " << c << endl;
	list<Cell*> path = GAMEINST->getGrid()->pathFinder.getPathAStar(_hisCell, &c);

	try{
		if (path.empty())
			throw "no path found";
		else if (path.size() > (unsigned int)_movementPoints && moveWanted)
			throw "not enough movement point";
		for (Cell* c : path)
		{
			moveSingle(*c, moveWanted);
		}
	}
	catch (const char* msg)
	{
		LOGERR << "cannot move: " << msg << endl;
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
bool Character::move(unsigned int cell, bool moveWanted)
{
	Cell* c = GAMEINST->getGrid()->getCell(cell);
	if (c != nullptr)
		return move(*c, moveWanted);

	return false;
}

void Character::beginTurn()
{
	_myTurn = true;
	/* add actions to the 'menu' */
	UI->addAction(Action(Callback(&Character::targetSelectorForCell, this, ACTION_MOVE), "Move"));
		
	UI->addAction(Action(Callback(&Character::targetSelectorForCharacter, this, Character::BASIC_ATTACK), "Basic attack"));
	/* casting a spell isn't handled by character but by each class (archer, knight, ..) */
	//UI->addAction(Action(Callback(&Character::actionCallback, this, ACTION_CAST), "Cast a spell"));

	
	/* reset the stats to normal */
	_capacityPoints = cpMax;
	_movementPoints = mpMax;
	_bonusDamage = 0;

	/* apply all the effects */
	for (OverTimeEffect* e : _effects)
	{
		e->beginTurn();
	}
	/* update cooldown */
	for (auto s : _spells)
	{
		if(s.second)
			s.second->beginTurn();
	}
}
void Character::endTurn()
{
	LOGINFO << "Ending turn " << endl;
	_myTurn = false;
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
void Character::newCast(int spellID, void* target)
{
	if (target == nullptr)
		target = this;
	if (_spells.count(spellID))
		_spells[spellID]->cast((Character*)target);
}

void Character::targetSelectorForCell(int spellID, void* d)
{
	LOGWARN << "targetSelectorForCell: depreciated, you should not call this func" << endl;
	
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
	LOGWARN << "targetSelectorForCharacter: depreciated, you should not call this func" << endl;
	
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

void Character::displayBasic(ostream& o) const
{
	o << _name;
}

void Character::targetSelector(int spellID, void* target)
{
	LOGINFO << "Select your target: " << endl;
	GAMEINST->displayPlayersList(LOGINFO);
	int c;
	cin >> c;
	try{
		Character *target = GAMEINST->getPlayer(c);
		newCast(spellID, target);
	}
	catch (const std::out_of_range& oor) {
		LOGERR << "Out of Range error: " << oor.what() << " (player does not exists)\n";
	}
}
ostream& operator<<(ostream& o, const Character& c)
{
	o << "Displaying: " << c._name << endl;
	o << "|-- Position: " << c._hisCell->getPosX() << "," << c._hisCell->getPosY() << endl;
	//o << "Stats: " << endl;
	o << "|-- HP: " << c._hitPoints << "/" << c.hpMax << endl;
	o << "|-- MP: " << c._movementPoints << endl;
	o << "|-- CP: " << c._capacityPoints << endl;
	o << "|-- DB: " << c._bonusDamage << endl;
	//o << "|-- HT: " << c._myTurn << endl;
	//o << "|-- DoT: " << c._damageOverTime << endl;

	return o;
}

