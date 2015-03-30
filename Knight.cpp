#include "Knight.h"


Knight::Knight(int x , int y , string name) : Character(x, y, name)
{
	// Initializing the Knight's HP, MP and CP with it's constants.
	mpMax = MP_MAX;
	cpMax = CP_MAX;
	hpMax = _hitPoints = HP_MAX;
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

	if (this->getCell()->getDistance(c) <= range && _capacityPoints >= cost)
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
}
void Knight::swordForward(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 6; // Only in line                    //
	int amountOfDamages = 90;                         //
	int cost = 5;                                     //
	////////////////////////////////////////////////////

	if (this->getCell()->getDistance(c) <= range && _capacityPoints >= cost &&
		(this->getCell()->getPosX() == c.getCell()->getPosX() || this->getCell()->getPosY() == c.getCell()->getPosY()))
	{
		// Launch projectile (animation) { TO BE ADD ! }
		c.lowerHitPoint(amountOfDamages); // The ennemy c takes a hit.
		LOGINFO << this->getName() << " : Casting swordForward on " << c.getName() << "(" << c.getId() << ")" << endl;
		_capacityPoints -= cost;
	}
	else
		LOGWARN << this->getName() << " : Fail cast swordForward" << endl;
}

void Knight::heal()
{
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

	
}

void Knight::swordOfDestiny(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 1;                                    //
	int amountOfDamages = 250;                        //
	int cost = 10;                                    //
	////////////////////////////////////////////////////

	if (this->getCell()->getDistance(c) <= range && _capacityPoints >= cost)
	{
		c.lowerHitPoint(amountOfDamages); // The ennemy c takes a hit.
		_capacityPoints -= cost;
		LOGINFO << this->getName() << " : Casting swordOfDestiny on " << c.getName() << "(" << c.getId() << ")" << endl;
	}
	else
		LOGWARN << this->getName() << " : Fail cast swordOfDestiny" << endl;
}
void Knight::beginTurn()
{
	UI->addAction(Action(Callback(&Character::targetSelectorForCell, this, Knight::DASH), "Cast Dash"));
	UI->addAction(Action(Callback(&Character::targetSelectorForCharacter, this, Knight::SWORD_FORWARD), "Cast Sword Forward"));
	UI->addAction(Action(Callback(&Knight::cast, this, Knight::HEAL), "Cast Heal"));
	UI->addAction(Action(Callback(&Character::targetSelectorForCharacter, this, Knight::SWORD_DESTINY), "Cast Sword Of Destiny"));
	Character::beginTurn();
}