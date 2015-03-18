#include "Knight.h"


Knight::Knight(string name) : Character(name)
{
	// Initializing the Knight's HP, MP and CP with it's constants.
	_movementPoints = MP_MAX;
	_capacityPoints = CP_MAX;
	_hitPoints = HP_MAX;
}


Knight::~Knight()
{
}

bool Knight::basicAttack(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 1;                                    //
	int amountOfDamages = 70;                         //
	int cost = 2;                                     //
	////////////////////////////////////////////////////

	bool attackHits = false;

	/*
	if (getDistance(this, c) <= range and _capacityPoints >= cost)
	{
		c.lowerHitPoint(amountOfDamages); // The ennemy c takes a hit.
		attackHits = true;
	}
	*/
	return (attackHits);
}

bool Knight::dash(/*const Cell & c*/)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 2;                                    //
	int cost = 3;                                     //
	////////////////////////////////////////////////////

	bool spellCasted = false;
	
	if (_capacityPoints >= cost)
	{
		// TELEPORT ME TO THE POINT YAY !
		spellCasted = true;
	}

	return (spellCasted);
}
bool Knight::swordForward(/*const Cell & c*/)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 6; // Only in line                    //
	int amountOfDamages = 90;                         //
	int cost = 5;                                     //
	////////////////////////////////////////////////////

	bool spellHits = false;

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

	/*
	if (getDistance(this, c) <= range and _capacityPoints >= cost)
	{
		c.lowerHitPoint(amountOfDamages); // The ennemy c takes a hit.
		spellHits = true;
	}
	*/

	return (spellHits);
}