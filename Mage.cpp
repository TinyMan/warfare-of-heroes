#include "Mage.h"
#include "Spell.h"
#include "RootEffect.h"
#include "DamageEffect.h"
#include "DamageBuffEffect.h"
#include "DiamondSelector.h"

Mage::Mage(int x, int y, string name) : Character(x, y, name)
{
	_type = "mage";
	// Initializing the Archer's HP, MP and CP with it's constants.
	mpMax = MP_MAX;
	cpMax = CP_MAX;
	hpMax = _hitPoints = HP_MAX;

	_spells[ROOT] = new Spell("Root", this, 3, 6, 0, 0, 0, 7, false);
	_spells[ROOT]->setDescription("Removes all the Movement Points of the target for 1 turn.");
	_spells[ROOT]->addEffect(new RootEffect(1, this));

	_spells[FIREBALL] = new Spell("Fireball of the Doom", this, 2, 5, 0, 0, 0, 4, false);
	_spells[FIREBALL]->setDescription("Throws a huge fireball at an enemy,\n dealing tons of damages and increasing \nthe Mage’s next turn damages.");
	_spells[FIREBALL]->addEffect(new DamageEffect(150, this));
	DamageBuffEffect* e = new DamageBuffEffect(200, 3, this);
	e->setTarget(this);
	_spells[FIREBALL]->addEffect(e);

	_spells[THUNDER] = new Spell("Thunder Storm", this, 1, 5, 0, 0, 0, 5, true);
	_spells[THUNDER]->setDescription("Launches a thunderstorm upon an area,\n dealing damages to all the targets present in that area.");
	_spells[THUNDER]->addEffect(new DamageEffect(80, this));
	_spells[THUNDER]->setTargetSelector(new DiamondSelector(2));

	_spells[ERUPTION] = new Spell("Eruption", this, 3, 4, 0, 0, 0, 7, false);
	_spells[ERUPTION]->setDescription("Causes the floor to burn for 3 turn,\n each player standing on a burned cell \ntakes damages at the beginning of his turn.");
	_spells[ERUPTION]->addEffect(new DamageOverTime(100, 6, this, "Eruption DoT"));
	_spells[ERUPTION]->setTargetSelector(new DiamondSelector(2));
	
	
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

	if (this->getDistance(c) <= range && _capacityPoints >= cost)
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
	LOGWARN << "thunderStorm: depreciated, you should not call this func" << endl;
	/*
	///////////////STATS OF THE SPELL///////////////////
	int range = 5; // Only in line                    //
	int amountOfDamages = 80;                         //
	int cost = 6;                                     //
	////////////////////////////////////////////////////

	// TODO : En ligne, AoE

	LOGINFO << this->getName() << " : Casting thunder storm on (" << c.getPosX() << "," << c.getPosY() << ")." << endl;
	*/
}

void Mage::eruption(const Cell & c)
{
	LOGWARN << "eruption: depreciated, you should not call this func" << endl;
	/*
	///////////////STATS OF THE SPELL///////////////////
	int range = 7;                                    //
	int amountOfDamages = 70;                         //
	int cost = 4;                                     //
	////////////////////////////////////////////////////

	// TODO : AoE dégats

	LOGINFO << this->getName() << " : Casting eruption on (" << c.getPosX() << "," << c.getPosY() << ")." << endl;
	*/
}

void Mage::rooting(Character & c)
{
	LOGWARN << "rooting: depreciated, you should not call this func" << endl;
	/*
	///////////////STATS OF THE SPELL///////////////////
	int range = 7;                                    //
	int amountOfMPRemoved = 1;                        //
	int cost = 4;                                     //
	////////////////////////////////////////////////////
	
	if (this->getDistance(c) <= range && _capacityPoints >= cost)
	{
		// Launch projectile (animation) { TO BE ADD ! }
		c.removeMovementPoint(amountOfMPRemoved);
		LOGINFO << this->getName() << " : Casting rooting on " << c.getName() << "(" << c.getId() << ")" << endl;
		_capacityPoints -= cost;
	}
	else
		LOGWARN << this->getName() << " : Fail cast rooting" << endl;
		*/
}

void Mage::fireBallOfTheDoom(Character & c)
{
	LOGWARN << "fireBallOfTheDoom: depreciated, you should not call this func" << endl;
	/*
	///////////////STATS OF THE SPELL///////////////////
	int range = 4;                                    //
	int amountOfDamages = 150;                        //
	int cost = 5;                                     //
	////////////////////////////////////////////////////

	if (this->getDistance(c) <= range && _capacityPoints >= cost)
	{
		// Launch projectile (animation) { TO BE ADD ! }
		c.lowerHitPoint(amountOfDamages+_bonusDamage); // The ennemy c takes a hit.
		_bonusDamage += 20;
		LOGINFO << this->getName() << " : Casting fireBall on " << c.getName() << "(" << c.getId() << ")" << endl;
		_capacityPoints -= cost;
	}
	else
		LOGWARN << this->getName() << " : Fail Cast fireBall" << endl;
		*/
}
void Mage::beginTurn()
{
	auto aoeSelector = [this](int radius, int spellID, void*)
	{
		int x, y;
		LOGINFO << "Enter cell position (e.g. 13 29): " << endl;
		cin >> x >> y;
		try{
			Cell* c = GAMEINST->getGrid()->getCellAt(x, y);
			if (c == nullptr) throw std::out_of_range("cell does not exists");			
			getSpell(spellID)->cast(new DiamondAoE(c, radius));
		}
		catch (const std::out_of_range& oor) {
			LOGERR << "Out of Range error: " << oor.what() << " (cell does not exists)\n";
		}
	};
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
	UI->addAction(Action(Callback(&Character::targetSelector, this, Mage::FIREBALL), "Cast Fireball Of The Doom"));
	UI->addAction(Action(Callback(&Character::targetSelector, this, Mage::ROOT), "Cast Root"));
	UI->addAction(Action(Callback(aoeSelector, 2, Mage::ERUPTION), "Cast Eruption"));
	UI->addAction(Action(Callback(aoeSelector, 2, Mage::THUNDER), "Cast Thunder Storm"));
	Character::beginTurn();
}
void Mage::endTurn()
{
	Character::endTurn();
}