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
	static const int DMG_BUFF = 0;
	static const int FLAMED_ARROW = 1;
	static const int SB_ARROW = 2;
	static const int VOLLEY = 3;
	

	Archer(string name="Legolas");
	~Archer();

	virtual bool basicAttack(Character & c);
	virtual bool cast(int spellID, void* data);

	// Spells :
	virtual bool damageBuff(); // Spell 1 : rises the damages the Archer does for a certain time.
	virtual bool flamedArrow(Character & c); // Spell 2 : lauches a fire arrow that burns the enemy for a certain time. 
	virtual bool stepBackArrow(Character & c); // Spell 3 : forces the opponent to fly back in a line away from the Archer.
	virtual bool arrowVolley(Character & c); // Spell 4 : launches a bunch of arrow in a cone to deal AreaOfEffect damages.

	// DO NOT FORGET : Implement cooldowns.

	
};

