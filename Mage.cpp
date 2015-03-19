#include "Mage.h"

// TODO : Prendre en compte les dégats bonus !


Mage::Mage(string name) : Character(name)
{
	// Initializing the Archer's HP, MP and CP with it's constants.
	_movementPoints = MP_MAX;
	_capacityPoints = CP_MAX;
	_hitPoints = HP_MAX;
}


Mage::~Mage()
{
}

bool Mage::basicAttack(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 4;                                    //
	int amountOfDamages = 40;                         //
	int cost = 1;                                     //
	////////////////////////////////////////////////////

	bool attackHits = false;

	/* TODO : utiliser getDistance pour coder les sorts
	if (getDistance(this, c) <= range or _capacityPoints >= cost)
	{
		// Launch projectile (animation) { TO BE ADD ! }
		c.lowerHitPoint(amountOfDamages); // The ennemy c takes a hit.
		attackHits = true;
	}
	*/
	return (attackHits);
}

bool Mage::thunderStorm(/*const Cell & c*/)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 5; // Only in line                    //
	int amountOfDamages = 80;                         //
	int cost = 6;                                     //
	////////////////////////////////////////////////////

	bool spellHits = false;

	return (spellHits);
}

bool Mage::eruption(/*const Cell & c*/)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 7;                                    //
	int amountOfDamages = 70;                         //
	int cost = 4;                                     //
	////////////////////////////////////////////////////

	bool spellHits = false;

	return (spellHits);
}

bool Mage::rooting(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 7;                                    //
	int amountOfMPRemoved = 1;                        //
	int cost = 4;                                     //
	////////////////////////////////////////////////////
	
	bool spellCasted = false;

	/* TODO
	if (_capacityPoints >= cost and getDistance(this, c) <= range)
	{
		c.removeMovementPoint(amountOfMPRemoved);
		spellCasted = true;
	}
	*/

	return (spellCasted);
}

bool Mage::fireBallOFTheDoom(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 4;                                    //
	int amountOfDamages = 150;                        //
	int cost = 4;                                     //
	////////////////////////////////////////////////////

	bool spellHits = false;

	/* TODO :
	if (_capacityPoints >= cost and getDistance(this, c) <= range)
	{
		c.lowerHitPoint(amountOfDamages);
		_bonusDamage += 20;
		spellHits = true;
	}
	*/

	return(spellHits);
}