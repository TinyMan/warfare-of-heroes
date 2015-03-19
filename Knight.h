#pragma once
#include "Character.h"

class Knight : public Character
{
protected:
	const static int MP_MAX = 4;
	const static int CP_MAX = 10;
	const static int HP_MAX = 800;
public:
	Knight(string name="Aragorn");
	~Knight();

	// Spells :
	bool basicAttack(Character & c);
	bool dash(/*const Cell & c*/); // Spell 1 : dashes to a cell, range = 2/3 ?
	bool swordForward(/*const Cell & c*/); // Spell 2 : only in line, extends the sword and deals damages
	bool heal(); // Spell 3 : heal the Knight for a certain amount of HP
	bool swordOfDestiny(Character & c); // Spell 4 : Bring down from the sky the ultimate sword, destroy anything

};

