#pragma once
#include "Character.h"
#include "Cell.h"

class Knight : public Character
{
protected:
	const static int MP_MAX = 4;
	const static int CP_MAX = 10;
	const static int HP_MAX = 800;
public:
	static const int DASH = 0;
	static const int SWORD_FORWARD = 1;
	static const int HEAL = 2;
	static const int SWORD_DESTINY = 3;

	Knight(string name="Aragorn");
	~Knight();

	virtual void cast(int spellID, void* data);

	virtual void basicAttack(Character & c);
	
	// begin turn
	virtual void beginTurn(){};
	virtual void endTurn(){};

	// Spells :
	virtual bool dash(const Cell & c); // Spell 1 : dashes to a cell, range = 2/3 ?
	virtual bool swordForward(const Cell & c); // Spell 2 : only in line, extends the sword and deals damages
	virtual bool heal(); // Spell 3 : heal the Knight for a certain amount of HP
	virtual bool swordOfDestiny(Character & c); // Spell 4 : Bring down from the sky the ultimate sword, destroy anything

};

