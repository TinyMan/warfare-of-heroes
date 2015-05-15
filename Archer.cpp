#include "Archer.h"
#include "Spell.h"
#include "DamageEffect.h"
#include "DamageOverTime.h"
#include "DamageBuffEffect.h"
#include "KnockBackEffect.h"

Archer::Archer(int x, int y, string name) : Character(x, y, name)
{
	// Initializing the Archer's HP, MP and CP with it's constants.
	mpMax = MP_MAX;
	cpMax = CP_MAX;
	hpMax = _hitPoints = HP_MAX;

	_spells[VOLLEY] = new Spell("Arrow Volley", this, 4, 10, 0, 0, 0, 8, false);
	_spells[VOLLEY]->setDescription("Shoots a bunch of arrows in the air, \nwhich then fall into a zone, dealing damages to the enemies present in the area.");
	_spells[VOLLEY]->addEffect(new DamageEffect(120, this));

	_spells[SB_ARROW] = new Spell("Step-Back Arrow", this, 4, 6, 0, 0, 0, 3, true);
	_spells[SB_ARROW]->setDescription("Shoots an arrow in a line, \nupon hitting an enemy, it makes him move backwards for 2 cells.");
	_spells[SB_ARROW]->addEffect(new KnockBackEffect(2, this));
	_spells[SB_ARROW]->addEffect(new DamageEffect(70, this));

	_spells[FLAMED_ARROW] = new Spell("Flamed Arrow", this, 4, 5, 0, 0, 0, 6, false);
	_spells[FLAMED_ARROW]->setDescription("Launches an arrow set on fire to damage and cause a 3 turn burn to the enemy. ");
	_spells[FLAMED_ARROW]->addEffect(new DamageEffect(80, this));
	_spells[FLAMED_ARROW]->addEffect(new DamageOverTime(20, 3, this, "Flamed Arrow DoT"));

	_spells[DMG_BUFF] = new Spell("Damage Buff", this, 4, 4, 0, 0, 0, 0, false);
	_spells[DMG_BUFF]->setDescription("Increases the Archer’s damages for a turn.");
	_spells[DMG_BUFF]->addEffect(new DamageBuffEffect(20, 3, this));
}


Archer::~Archer()
{
}

void Archer::cast(int spellID, void* data)
{
	LOGWARN << "cast: depreciated, you should not call this func" << endl;
	/*
	switch (spellID)
	{
	case Character::BASIC_ATTACK:
		basicAttack(*(Character*)data);
		break;
	case Archer::DMG_BUFF:
		_spells[DMG_BUFF]->cast(this);
		break;
	case Archer::FLAMED_ARROW:
		_spells[FLAMED_ARROW]->cast((Character*)data);
		//flamedArrow(*(Character*)data);
		break;
	case Archer::SB_ARROW:
		stepBackArrow(*(Character*)data);
		break;
	case Archer::VOLLEY:
		//arrowVolley(*(Character*)data);
		_spells[VOLLEY]->cast((Character*)data);
		break;
	default:
		break;
	}*/
}

void Archer::basicAttack(Character & c)
{
	///////////////STATS OF THE SPELL///////////////////
	int range = 6;                                    //
	int amountOfDamages = 50;                         //
	int cost = 2;                                     //
	////////////////////////////////////////////////////

	if (this->getDistance(c) <= range && _capacityPoints >= cost)
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
	LOGWARN << "damageBuff: depreciated, you should not call this func" << endl;
	/*
	////////STATS OF THE SPELL///////
	int cost = 4;                  //
	/////////////////////////////////

	if (_capacityPoints >= cost)
	{
		_bonusDamage += 20;
		LOGINFO << this->getName() << " : Casting damageBuff on himself (" << this->getId() << ") : +20 damages." << endl;
		_capacityPoints -= cost;
	}
	else
		LOGWARN << this->getName() << " : Fail cast damageBuff (not enough CP)" << endl;
		*/
}

void Archer::flamedArrow(Character & c)
{
	LOGWARN << "flamedArrow: depreciated, you should not call this func" << endl;
	/*
	///////////////STATS OF THE SPELL///////////////////
	int range = 6; //                                 //
	int amountOfDamages = 80;                         //
	int dot = 20;                                     //
	int cost = 5;                                     //
	////////////////////////////////////////////////////

	if (this->getDistance(c) <= range && _capacityPoints >= cost)
	{

		// Launch projectile (animation) { TO BE ADD ! }
		c.lowerHitPoint(amountOfDamages); // The ennemy c takes a hit.
		LOGINFO << this->getName() << " : Casting flamedArrow on " << c.getName() << "(" << c.getId() << ")" << endl;
//		c.setDoT(dot);
		_capacityPoints -= cost;
	}
	else
		LOGWARN << this->getName() << " : Fail cast flamedArrow" << endl;
		*/
}

void Archer::stepBackArrow(Character & c)
{
	LOGWARN << "stepBackArrow: depreciated, you should not call this func" << endl;
	/*
	///////////////STATS OF THE SPELL///////////////////
	int range = 3;                                    //
	int amountOfDamages = 70;                         //
	int cost = 6;                                     //
	////////////////////////////////////////////////////

	if (this->getDistance(c) <= range && _capacityPoints >= cost)
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
		*/	
}

void Archer::arrowVolley(Character & c)
{
	LOGWARN << "arrowVolley: depreciated, you should not call this func" << endl;
	/*
	///////////////STATS OF THE SPELL///////////////////
	int range = 8;                                    //
	int amountOfDamages = 120;                        //
	int cost = 10;                                    //
	////////////////////////////////////////////////////
	if (this->getDistance(c) <= range && _capacityPoints >= cost)
	{
		// Launch projectile (animation) { TO BE ADD ! }
		c.lowerHitPoint(amountOfDamages); // The ennemy c takes a hit.
		LOGINFO << this->getName() << " : Casting arrowVolley on " << c.getName() << "(" << c.getId() << ")" << endl;
		_capacityPoints -= cost;
	}
	else
		LOGWARN << this->getName() << " : Fail cast arrowVolley" << endl;
		*/
}

void Archer::beginTurn()
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

	UI->addAction(Action(Callback(&Character::targetSelector, this, Archer::VOLLEY), "Cast Arrow Volley"));
	UI->addAction(Action(Callback(&Character::targetSelector, this, Archer::SB_ARROW), "Cast Step Back Arrow"));
	UI->addAction(Action(Callback(&Character::targetSelector, this, Archer::FLAMED_ARROW), "Cast Flamed Arrow"));
	UI->addAction(Action(Callback(&Character::newCast, this, Archer::DMG_BUFF), "Cast Damage Buff"));
	Character::beginTurn();
}
void Archer::endTurn()
{
	Character::endTurn();
}
