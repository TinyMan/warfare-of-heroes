#pragma once
#include "Character.h"

class Archer : public Character
{
protected:
	const static int MP_MAX = 3;
	const static int CP_MAX = 10;
	const static int HP_MAX = 680;

	
public:
	static const int DMG_BUFF = 0;
	static const int FLAMED_ARROW = 1;
	static const int SB_ARROW = 2;
	static const int VOLLEY = 3;
	

	Archer(int x = 0, int y = 0, string name="Legolas");
	~Archer();

	virtual void basicAttack(Character & c);
	virtual void cast(int spellID, void* data);
	// begin turn
	virtual void beginTurn();
	virtual void endTurn();

	// Spells :
	virtual void damageBuff(); // Spell 1 : rises the damages the Archer does for a certain time.
	virtual void flamedArrow(Character & c); // Spell 2 : lauches a fire arrow that burns the enemy for a certain time. 
	virtual void stepBackArrow(Character & c); // Spell 3 : forces the opponent to fly back in a line away from the Archer.
	virtual void arrowVolley(Character & c); // Spell 4 : launches a bunch of arrow in a cone to deal AreaOfEffect damages.

	// DO NOT FORGET : Implement cooldowns.

	
};

