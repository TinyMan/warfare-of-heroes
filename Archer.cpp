#include "Archer.h"

Archer::Archer(int x, int y, string name) : Character(x, y, name)
{
	// Initializing the Archer's HP, MP and CP with it's constants.
	mpMax = MP_MAX;
	cpMax = CP_MAX;
	hpMax = _hitPoints = HP_MAX;
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
	int range = 6;                                    //
	int amountOfDamages = 50;                         //
	int cost = 2;                                     //
	////////////////////////////////////////////////////

	if (this->getCell()->getDistance(c) <= range && _capacityPoints >= cost)
	{
		// Launch projectile (animation) { TO BE ADD ! }
		c.lowerHitPoint(amountOfDamages+_bonusDamage); // The ennemy c takes a hit.
		LOGINFO << this->getName() << " : Casting basicAttack on " << c.getName() << "(" << c.getId() << ")" << endl;
		_capacityPoints -= cost;
	}
	else
		LOGWARN << this->getName() << " : Fail cast basicAttack" << endl;
}

void Archer::damageBuff()
{
	////////STATS OF THE SPELL///////
	int cost = 4;                  //
	/////////////////////////////////

	if (_capacityPoints >= cost)
	{
		_bonusDamage += 20;
		/* Lancement du sort : affichage */
		LOGINFO << this->getName() << " : Casting damageBuff on himself (" << this->getId() << ") : +20 damages." << endl;
		_capacityPoints -= cost;
	}
	else
		LOGWARN << this->getName() << " : Fail cast damageBuff (not enough CP)" << endl;
}

void Archer::flamedArrow(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 6; //                                 //
	int amountOfDamages = 80;                         //
	int dot = 20;                                     //
	int cost = 5;                                     //
	////////////////////////////////////////////////////

	if (this->getCell()->getDistance(c) <= range && _capacityPoints >= cost)
	{
		// Launch projectile (animation) { TO BE ADD ! }
		c.lowerHitPoint(amountOfDamages); // The ennemy c takes a hit.
		LOGINFO << this->getName() << " : Casting flamedArrow on " << c.getName() << "(" << c.getId() << ")" << endl;
		c.setDoT(dot);
		_capacityPoints -= cost;
	}
	else
		LOGWARN << this->getName() << " : Fail cast flamedArrow" << endl;
}

void Archer::stepBackArrow(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 3;                                    //
	int amountOfDamages = 70;                         //
	int cost = 6;                                     //
	////////////////////////////////////////////////////

	if (this->getCell()->getDistance(c) <= range && _capacityPoints >= cost)
	{
		// Launch projectile (animation) { TO BE ADD ! }
		if (this->getCell()->getPosX() == c.getCell()->getPosX())
		{
			c.move(c.getCell()->getPosX() + 2, c.getCell()->getPosY(), false);
			c.lowerHitPoint(amountOfDamages); // The ennemy c takes a hit.
			LOGINFO << this->getName() << " : Casting stepBackArrow on " << c.getName() << "(" << c.getId() << ")" << endl;
			_capacityPoints -= cost;
		}
		else if (this->getCell()->getPosY() == c.getCell()->getPosY())
		{
			c.move(c.getCell()->getPosX(), c.getCell()->getPosY() + 2, false);
			c.lowerHitPoint(amountOfDamages); // The ennemy c takes a hit.
			LOGINFO << this->getName() << " : Casting stepBackArrow on " << c.getName() << "(" << c.getId() << ")" << endl;
			_capacityPoints -= cost;
		}
	}
	else
		LOGWARN << this->getName() << " : Fail cast stepBackArrow" << endl;
	
}

void Archer::arrowVolley(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 8;                                    //
	int amountOfDamages = 120;                        //
	int cost = 10;                                    //
	////////////////////////////////////////////////////
	if (this->getCell()->getDistance(c) <= range && _capacityPoints >= cost)
	{
		// Launch projectile (animation) { TO BE ADD ! }
		c.lowerHitPoint(amountOfDamages); // The ennemy c takes a hit.
		LOGINFO << this->getName() << " : Casting arrowVolley on " << c.getName() << "(" << c.getId() << ")" << endl;
		_capacityPoints -= cost;
	}
	else
		LOGWARN << this->getName() << " : Fail cast arrowVolley" << endl;
}

void Archer::beginTurn()
{
	
	UI->addAction(Action(Callback(&Character::targetSelectorForCharacter, this, Archer::VOLLEY), "Cast Arrow Volley"));
	UI->addAction(Action(Callback(&Character::targetSelectorForCharacter, this, Archer::SB_ARROW), "Cast Step Back Arrow"));
	UI->addAction(Action(Callback(&Character::targetSelectorForCharacter, this, Archer::FLAMED_ARROW), "Cast Flamed Arrow"));
	UI->addAction(Action(Callback(&Archer::cast, this, Archer::DMG_BUFF), "Cast Damage Buff"));
	Character::beginTurn();
}
