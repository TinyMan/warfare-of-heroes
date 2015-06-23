#include "Knight.h"
#include "Spell.h"
#include "HealEffect.h"
#include "DashEffect.h"
#include "DamageEffect.h"
#include "LineAoE.h"
#include "BasicLineSelector.h"


Knight::Knight(int x , int y , string name) : Character(x, y, name)
{
	_type = "knight";
	// Initializing the Knight's HP, MP and CP with it's constants.
	mpMax = MP_MAX;
	cpMax = CP_MAX;
	hpMax = _hitPoints = HP_MAX;

	_spells[DASH] = new Spell("Dash", this, 0, 3, 0, 0, 0, 2, false);
	_spells[DASH]->setDescription("The Knight leaps forward to a maximum of 2 cells.");
	_spells[DASH]->addEffect(new DashEffect(this));

	_spells[HEAL] = new Spell("Heal", this, 2, 4, 0, 0, 0, 0, false);
	_spells[HEAL]->setDescription("Calls the mighty magic healing upon the Knight.");
	_spells[HEAL]->addEffect(new HealEffect(50, this));

	_spells[SWORD_DESTINY] = new Spell("Sword of Destiny", this, 3, 10, 0, 0, 0, 1, false);
	_spells[SWORD_DESTINY]->setDescription("The almighty Sword of Destiny comes from the sky to slay an enemy, \ndealing huge damages to a single target.");
	_spells[SWORD_DESTINY]->addEffect(new DamageEffect(250, this));

	_spells[SWORD_FORWARD] = new Spell("Sword Forward", this, 1, 4, 0, 0, 0, 6, true);
	_spells[SWORD_FORWARD]->setDescription("Expends its sword in a line to damage all the enemies within that line.");
	_spells[SWORD_FORWARD]->addEffect(new DamageEffect(90, this));
	_spells[SWORD_FORWARD]->setTargetSelector(new BasicLineSelector(6, [=](Cell* second, Grid::DIRECTION * dir){
		const Cell* first = getCell();
		if (first == second) throw("First cell and Second cell should not be the same !");
		Grid * grid = GAMEINST->getGrid();
		Grid::DIRECTION d = grid->getDir(*first, *second);

		Cell* _last = grid->getCellFromCellAndDir(*first, d, 1);
		if (dir)
			*dir = d;
		return _last; 
	}));
	
}


Knight::~Knight()
{
}

void Knight::cast(int spellID, void* data)
{
	
	switch (spellID)
	{
	case Character::BASIC_ATTACK:
		basicAttack(*(Character*)data);
		break;
	case Knight::DASH:
	{
		dash(*(Cell*)data); 
		break;
	}
	case Knight::SWORD_FORWARD:
	{
		swordForward(*(Character*)data);
		break;
	}
	case Knight::HEAL:
	{
		heal(); 
		break;
	}
	case Knight::SWORD_DESTINY:
	{
		swordOfDestiny(*(Character*)data);
		break;
	}
	default:
		break;
	}
}

void Knight::basicAttack(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 1;                                    //
	int amountOfDamages = 70;                         //
	int cost = 2;                                     //
	////////////////////////////////////////////////////

	if (this->getDistance(c) <= range && _capacityPoints >= cost)
	{
		// Launch projectile (animation) { TO BE ADD ! }
		c.lowerHitPoint(amountOfDamages); // The ennemy c takes a hit.
		LOGINFO << this->getName() << " : Casting basicAttack on " << c.getName() << "(" << c.getId() << ")" << endl;
		_capacityPoints -= cost;
	}
	else
		LOGWARN << this->getName() << " : Fail cast basicAttack" << endl;
}

void Knight::dash(Cell & c)
{
	LOGWARN << "dash: depreciated, you should not call this func" << endl;
	/*
	///////////////STATS OF THE SPELL///////////////////
	int range = 2;                                    //
	int cost = 3;                                     //
	////////////////////////////////////////////////////
	
	if (_capacityPoints >= cost && getCell()->getDistance(c)<= range)
	{
		// TELEPORT ME TO THE POINT YAY !
		LOGINFO << this->getName() << " : Casting dash !" << endl;
		this->move(c);
		_capacityPoints -= cost;
	}
	else
		LOGWARN << this->getName() << " : Fail cast dash" << endl;
		*/
}
void Knight::swordForward(Character & c)
{
	LOGWARN << "swordForward: depreciated, you should not call this func" << endl;
	/*
	///////////////STATS OF THE SPELL///////////////////
	int range = 6; // Only in line                    //
	int amountOfDamages = 90;                         //
	int cost = 5;                                     //
	////////////////////////////////////////////////////

	if (this->getDistance(c) <= range && _capacityPoints >= cost &&
		(this->getCell()->getPosX() == c.getCell()->getPosX() || this->getCell()->getPosY() == c.getCell()->getPosY()))
	{
		// Launch projectile (animation) { TO BE ADD ! }
		c.lowerHitPoint(amountOfDamages); // The ennemy c takes a hit.
		LOGINFO << this->getName() << " : Casting swordForward on " << c.getName() << "(" << c.getId() << ")" << endl;
		_capacityPoints -= cost;
	}
	else
		LOGWARN << this->getName() << " : Fail cast swordForward" << endl;
		*/
}

void Knight::heal()
{
	LOGWARN << "heal: depreciated, you should not call this func" << endl;
	/*
	///////////////STATS OF THE SPELL///////////////////
	int range = 0;                                    //
	int amountOfDamages = -50;                        //
	int cost = 2;                                     //
	////////////////////////////////////////////////////

	if (_capacityPoints >= cost)
	{
		LOGINFO << this->getName() << " : Casting heal on himself (" << this->getId() << ")" << endl;
		this->lowerHitPoint(amountOfDamages);
		_capacityPoints -= cost;
	}
	else
		LOGWARN << this->getName() << " : Fail cast heal" << endl;

	*/
}

void Knight::swordOfDestiny(Character & c)
{
	LOGWARN << "swordOfDestiny: depreciated, you should not call this func" << endl;
	/*
	///////////////STATS OF THE SPELL///////////////////
	int range = 1;                                    //
	int amountOfDamages = 250;                        //
	int cost = 10;                                    //
	////////////////////////////////////////////////////

	if (this->getDistance(c) <= range && _capacityPoints >= cost)
	{
		c.lowerHitPoint(amountOfDamages); // The ennemy c takes a hit.
		_capacityPoints -= cost;
		LOGINFO << this->getName() << " : Casting swordOfDestiny on " << c.getName() << "(" << c.getId() << ")" << endl;
	}
	else
		LOGWARN << this->getName() << " : Fail cast swordOfDestiny" << endl;
		*/
}
void Knight::beginTurn()
{
	auto lambda = [this](int spellID, void*)
	{
		int x, y;
		LOGINFO << "Enter cell position (e.g. 13 29): " << endl;
		cin >> x >> y;
		try{
			Cell* c = GAMEINST->getGrid()->getCellAt(x, y);
			if (c == nullptr) throw std::out_of_range("cell does not exists");

			getSpell(spellID)->cast(c);
		}
		catch (const std::out_of_range& oor) {
			LOGERR << "Out of Range error: " << oor.what() << " (cell does not exists)\n";
		}
	};
	auto lineAoESelector = [this](int range, int spellID, void*)
	{
		int x, y;
		LOGINFO << "Enter cell position (e.g. 13 29): " << endl;
		cin >> x >> y;
		try{
			Cell* c = GAMEINST->getGrid()->getCellAt(x, y);
			if (c == nullptr) throw std::out_of_range("cell does not exists");
			Grid * g = GAMEINST->getGrid();
			LineAoE* aoe = new LineAoE(g->getCellFromCellAndDir(*this->_hisCell, g->getDir(*this->_hisCell, *c), 1), c, range);
			LOGINFO << *aoe << endl;
			getSpell(spellID)->cast(aoe);
		}
		catch (const std::out_of_range& oor) {
			LOGERR << "Out of Range error: " << oor.what() << " (cell does not exists)\n";
		}
		catch (const char* msg)
		{
			LOGERR << msg << endl;
		}
	};
		
	UI->addAction(Action(Callback(lambda, Knight::DASH), "Cast Dash"));
	UI->addAction(Action(Callback(lineAoESelector, _spells[SWORD_FORWARD]->getMaxScope(), Knight::SWORD_FORWARD), "Cast Sword Forward"));
	UI->addAction(Action(Callback(&Knight::newCast, this, Knight::HEAL), "Cast Heal"));
	UI->addAction(Action(Callback(&Character::targetSelector, this, Knight::SWORD_DESTINY), "Cast Sword Of Destiny"));
	Character::beginTurn();
}
void Knight::endTurn()
{
	Character::endTurn();
}