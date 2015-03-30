#include "Mage.h"

Mage::Mage(int x, int y, string name) : Character(x, y, name)
{
	// Initializing the Archer's HP, MP and CP with it's constants.
	mpMax = MP_MAX;
	cpMax = CP_MAX;
	hpMax = _hitPoints = HP_MAX;
}


Mage::~Mage()
{
}

void Mage::cast(int spellID, void* data)
{
	switch (spellID)
	{
	case Character::BASIC_ATTACK:
		basicAttack(*(Character*)data);
		break;
	case Mage::THUNDER:
		thunderStorm(*(Cell*)data);
		break;
	case Mage::ERUPTION:
		eruption(*(Cell*)data);
		break;
	case Mage::ROOT:
		rooting(*(Character*)data);
		break;
	case Mage::FIREBALL:
		fireBallOfTheDoom(*(Character*)data);
		break;
	default:
		break;
	}
}

void Mage::basicAttack(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 4;                                    //
	int amountOfDamages = 40;                         //
	int cost = 1;                                     //
	////////////////////////////////////////////////////

	if (this->getCell()->getDistance(c) <= range && _capacityPoints >= cost)
	{
		// Launch projectile (animation) { TO BE ADD ! }
		c.lowerHitPoint(amountOfDamages + _bonusDamage); // The ennemy c takes a hit.
		LOGINFO << this->getName() << " : Casting basicAttack on " << c.getName() << "(" << c.getId() << ")" << endl;
		_capacityPoints -= cost;
	}
	else
		LOGWARN << this->getName() << " : Fail cast basicAttack" << endl;
}

void Mage::thunderStorm(const Cell & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 5; // Only in line                    //
	int amountOfDamages = 80;                         //
	int cost = 6;                                     //
	////////////////////////////////////////////////////

	// TODO : En ligne, AoE

	LOGINFO << this->getName() << " : Casting thunder storm on (" << c.getPosX() << "," << c.getPosY() << ")." << endl;
}

void Mage::eruption(const Cell & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 7;                                    //
	int amountOfDamages = 70;                         //
	int cost = 4;                                     //
	////////////////////////////////////////////////////

	// TODO : AoE dégats

	LOGINFO << this->getName() << " : Casting eruption on (" << c.getPosX() << "," << c.getPosY() << ")." << endl;
}

void Mage::rooting(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 7;                                    //
	int amountOfMPRemoved = 1;                        //
	int cost = 4;                                     //
	////////////////////////////////////////////////////
	
	if (this->getCell()->getDistance(c) <= range && _capacityPoints >= cost)
	{
		// Launch projectile (animation) { TO BE ADD ! }
		c.removeMovementPoint(amountOfMPRemoved);
		LOGINFO << this->getName() << " : Casting rooting on " << c.getName() << "(" << c.getId() << ")" << endl;
		_capacityPoints -= cost;
	}
	else
		LOGWARN << this->getName() << " : Fail cast rooting" << endl;
}

void Mage::fireBallOfTheDoom(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 4;                                    //
	int amountOfDamages = 150;                        //
	int cost = 5;                                     //
	////////////////////////////////////////////////////

	if (this->getCell()->getDistance(c) <= range && _capacityPoints >= cost)
	{
		// Launch projectile (animation) { TO BE ADD ! }
		c.lowerHitPoint(amountOfDamages+_bonusDamage); // The ennemy c takes a hit.
		_bonusDamage += 20;
		LOGINFO << this->getName() << " : Casting fireBall on " << c.getName() << "(" << c.getId() << ")" << endl;
		_capacityPoints -= cost;
	}
	else
		LOGWARN << this->getName() << " : Fail Cast fireBall" << endl;
}
void Mage::beginTurn()
{
	UI->addAction(Action(Callback(&Character::targetSelectorForCharacter, this, Mage::FIREBALL), "Cast Fireball Of The Doom"));
	UI->addAction(Action(Callback(&Character::targetSelectorForCharacter, this, Mage::ROOT), "Cast Root"));
	UI->addAction(Action(Callback(&Character::targetSelectorForCell, this, Mage::ERUPTION), "Cast Eruption"));
	UI->addAction(Action(Callback(&Character::targetSelectorForCell, this, Mage::THUNDER), "Cast Thunder Storm"));
	Character::beginTurn();
}