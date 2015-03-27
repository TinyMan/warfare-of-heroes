#pragma once
#include "Character.h"
#include "Cell.h"

class Mage : public Character
{
protected:
	const static int MP_MAX = 2;
	const static int CP_MAX = 12;
	const static int HP_MAX = 750;
	int _bonusDamage = 0;

public:
	static const int THUNDER = 0;
	static const int ERUPTION = 1;
	static const int ROOT = 2;
	static const int FIREBALL = 3;

	Mage(int x = 0, int y = 0, string name = "Gandalf");
	~Mage();

	virtual void basicAttack(Character & c);
	virtual void cast(int spellID, void*);

	// begin turn
	virtual void beginTurn();
	virtual void endTurn(){};

	// Spells :
	virtual bool thunderStorm(const Cell & c); // Spell 1 : Only in line, throws an AoE of radius 2 that deals damages
	virtual bool eruption(const Cell & c); // Spell 2 : draws at the floor a deadzone of radius 2 that deals damages when you stand on it
	virtual bool rooting(Character & c); // Spell 3 : remove some MPs to the ennemy targeted
	virtual bool fireBallOfTheDoom(Character & c); // Spell 4 : burns an ennemy and increases the damage the Mage will deal next turn

	// DO NOT FORGET : Implement cooldowns.
};