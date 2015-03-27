#include "Knight.h"


Knight::Knight(int x , int y , string name) : Character(x, y, name)
{
	// Initializing the Knight's HP, MP and CP with it's constants.
	_movementPoints = MP_MAX;
	_capacityPoints = CP_MAX;
	_hitPoints = HP_MAX;
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
		swordForward(*(Cell*)data);
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

	bool attackHits = false;

	/* TODO : utiliser getDistance pour coder les sorts
	if (getDistance(this, c) <= range and _capacityPoints >= cost)
	{
		c.lowerHitPoint(amountOfDamages); // The ennemy c takes a hit.
		attackHits = true;
	}
	*/

	LOGINFO << this->getName() << " : Casting basicAttack on " << c.getName() << "(" << c.getId() << ")" << endl;

}

bool Knight::dash(const Cell & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 2;                                    //
	int cost = 3;                                     //
	////////////////////////////////////////////////////

	bool spellCasted = false;
	
	if (_capacityPoints >= cost)
	{
		// TELEPORT ME TO THE POINT YAY !
		LOGINFO << this->getName() << " : Casting dash !" << endl;
		spellCasted = true;
	}

	return (spellCasted);
}
bool Knight::swordForward(const Cell & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 6; // Only in line                    //
	int amountOfDamages = 90;                         //
	int cost = 5;                                     //
	////////////////////////////////////////////////////

	bool spellHits = false;

	LOGINFO << this->getName() << " : Casting swordForward on (" << c.getPosX() << "," << c.getPosY() << ")." << endl;

	return (spellHits);
}

bool Knight::heal()
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 0;                                    //
	int amountOfDamages = -50;                        //
	int cost = 2;                                     //
	////////////////////////////////////////////////////

	bool spellHits = false;

	LOGINFO << this->getName() << " : Casting heal on himself (" << this->getId() << ")" << endl;

	return (spellHits);
}

bool Knight::swordOfDestiny(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 1;                                    //
	int amountOfDamages = 250;                        //
	int cost = 10;                                    //
	////////////////////////////////////////////////////

	bool spellHits = false;

	/* TODO :
	if (getDistance(this, c) <= range and _capacityPoints >= cost)
	{
		c.lowerHitPoint(amountOfDamages); // The ennemy c takes a hit.
		spellHits = true;
	}
	*/

	LOGINFO << this->getName() << " : Casting swordOfDestiny on " << c.getName() << "(" << c.getId() << ")" << endl;

	return (spellHits);
}
void Knight::beginTurn()
{
	Character::beginTurn();
}