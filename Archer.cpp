#include "Archer.h"

// TODO : Prendre en compte les dégats bonus !

Archer::Archer(string name) : Character(name)
{
	// Initializing the Archer's HP, MP and CP with it's constants.
	_movementPoints = MP_MAX;
	_capacityPoints = CP_MAX;
	_hitPoints = HP_MAX;
}


Archer::~Archer()
{
}

bool Archer::cast(int spellID, void* data)
{
	bool ret = false;
	switch (spellID)
	{
	case Archer::DMG_BUFF:
		ret = damageBuff();
		break;
	case Archer::FLAMED_ARROW:
		ret = flamedArrow(*(Character*)data);
		break;
	case Archer::SB_ARROW:
		ret = stepBackArrow(*(Character*)data);
		break;
	case Archer::VOLLEY:
		ret = arrowVolley(*(Character*)data);
		break;
	default:
		break;
	}
	return ret;
}

bool Archer::basicAttack(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 6; // Random value, to be changed ?   //
	int amountOfDamages = 50;                         //
	int cost = 2;                                     //
	////////////////////////////////////////////////////
	
	bool attackHits = false;

	
	// TODO : Utiliser la fonction getDistance pour créer les sorts
	/*if (getDistance(this, c) <= range and _capacityPoints >= cost)
	{
		// Launch projectile (animation) { TO BE ADD ! }
		c.lowerHitPoint(amountOfDamages); // The ennemy c takes a hit.
		attackHits = true;
	}
	*/

	LOGINFO << this->getName() << " : Casting basicAttack on " << c.getName() << "(" << c.getId() << ")" << endl;

	return (attackHits);
}

bool Archer::damageBuff()
{
	////////STATS OF THE SPELL///////
	int cost = 4;                  //
	bool spellCasted = false;      //
	/////////////////////////////////

	if (_capacityPoints >= cost)
	{
		_bonusDamage += 20;
		spellCasted = true;
		/* Lancement du sort : affichage */
		LOGINFO << this->getName() << " : Casting damageBuff on himself (" << this->getId() << ") : +20 damages." << endl;
	}
	
	return (spellCasted);
}

bool Archer::flamedArrow(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 6; //                                 //
	int amountOfDamages = 80;                         //
	int cost = 5;                                     //
	////////////////////////////////////////////////////

	bool spellHits = false;

	LOGINFO << this->getName() << " : Casting flamedArrow on " << c.getName() << "(" << c.getId() << ")" << endl;

	return (spellHits);
}

bool Archer::stepBackArrow(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 3;                                    //
	int amountOfDamages = 70;                         //
	int cost = 6;                                     //
	////////////////////////////////////////////////////

	bool spellHits = false;

	LOGINFO << this->getName() << " : Casting stepBackArrow on " << c.getName() << "(" << c.getId() << ")" << endl;

	return (spellHits);
}

bool Archer::arrowVolley(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 8;                                    //
	int amountOfDamages = 100;                        //
	int cost = 10;                                    //
	////////////////////////////////////////////////////

	bool spellHits = false;
	LOGINFO << getName() << " casts Arrow volley on " << c.getName() << "(player id: " << c.getId() << ")" << endl;
	return (spellHits);
}

