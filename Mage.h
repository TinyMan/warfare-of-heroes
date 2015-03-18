#pragma once
#include "Character.h"

class Mage : public Character
{
protected:
	const static int MP_MAX = 2;
	const static int CP_MAX = 12;
	const static int HP_MAX = 750;
	int _bonusDamage = 0;

public:
	Mage(string name="Gandalf");
	~Mage();

	// Spells :
	bool basicAttack(Character & c);
	bool thunderStorm(/*const Cell & c*/); // Spell 1 : Only in line, throws an AoE of radius 2 that deals damages
	bool eruption(/*const Cell & c*/); // Spell 2 : draws at the floor a deadzone of radius 2 that deals damages when you stand on it
	bool rooting(Character & c); // Spell 3 : remove some MPs to the ennemy targeted
	bool fireBallOFTheDoom(Character & c); // Spell 4 : burns an ennemy and increases the damage the Mage will deal next turn

	// DO NOT FORGET : Implement cooldowns.
};