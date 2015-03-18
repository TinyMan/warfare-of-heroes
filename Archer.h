#pragma once
#include "Character.h"

class Archer : public Character
{
protected:
	const static int MP_MAX = 3;
	const static int CP_MAX = 10;
	const static int HP_MAX = 680;
	int _bonusDamage = 0;

public:
	Archer(string name="Legolas");
	~Archer();

	// Spells :
	bool basicAttack(Character & c); 
	bool damageBuff(); // Spell 1 : rises the damages the Archer does for a certain time.
	bool flamedArrow(Character & c); // Spell 2 : lauches a fire arrow that burns the enemy for a certain time. 
	bool stepBackArrow(Character & c); // Spell 3 : forces the opponent to fly back in a line away from the Archer.
	bool arrowVolley(Character & c); // Spell 4 : launches a bunch of arrow in a cone to deal AreaOfEffect damages.

	// DO NOT FORGET : Implement cooldowns.
};

