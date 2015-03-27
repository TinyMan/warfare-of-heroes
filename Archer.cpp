#include "Archer.h"

// TODO : Prendre en compte les dégats bonus !

Archer::Archer(int x, int y, string name) : Character(x, y, name)
{
	// Initializing the Archer's HP, MP and CP with it's constants.
	_movementPoints = MP_MAX;
	_capacityPoints = CP_MAX;
	_hitPoints = HP_MAX;
}


Archer::~Archer()
{
}

void Archer::cast(int spellID, void* data)
{
	switch (spellID)
	{
	case Character::BASIC_ATTACK:
		basicAttack(*(Character*)data);
		break;
	case Archer::DMG_BUFF:
		damageBuff();
		break;
	case Archer::FLAMED_ARROW:
		flamedArrow(*(Character*)data);
		break;
	case Archer::SB_ARROW:
		stepBackArrow(*(Character*)data);
		break;
	case Archer::VOLLEY:
		arrowVolley(*(Character*)data);
		break;
	default:
		break;
	}
}

void Archer::basicAttack(Character & c)
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

void Archer::beginTurn()
{
	
	UI->addAction(Action(Callback(&Character::targetSelectorForCharacter, this, Archer::VOLLEY), "Cast arrow volley"));
	UI->addAction(Action(Callback(&Character::targetSelectorForCharacter, this, Archer::SB_ARROW), "Cast step back arrow"));
	UI->addAction(Action(Callback(&Character::targetSelectorForCharacter, this, Archer::FLAMED_ARROW), "Cast flamed arrow"));
	UI->addAction(Action(Callback(&Archer::cast, this, Archer::DMG_BUFF), "Cast Damage buff"));
	Character::beginTurn();
}
