#pragma once
#include <iostream>
#include <vector>
#include "SpellTarget.h"
#include "GameObject.h"
#include "Game.h"
#include "DamageOverTime.h"
#include "CharacterEvents.h"
#include "Grid.h"
#include "TextureManager.h"
using namespace std;
using namespace Events::CharacterEvents;

class Cell;
class Spell;


/* abstract class */
class Character : public GameObject, public SpellTarget
{
private:
	static const int NB_SPELLS = 6; /* four spells + move + basic attack */

protected:
	string _name;
	string _type;
	int _hitPoints;
	int _movementPoints;
	int _capacityPoints;
	int _bonusDamage;
	list<OverTimeEffect*> _effects;
	int mpMax;
	int cpMax;
	int hpMax;
	Cell* _hisCell = nullptr;
	bool _myTurn = false;
	bool _dead = false;

	map<int, Spell*> _spells;
public:
	Character(int x = 0, int y = 0, string name = "NoName");
	virtual ~Character();

	// Setters :
	void lowerHitPoint(int amount=0);
	void heal(int amount = 0);
	void removeMovementPoint(int amount=1);
	void removeCapaciyPoint(int amount = 1);
	void addBonusDamage(int amount = 0);
	void addEffect(OverTimeEffect* e);
	void root();

	// Getters :
	string getName() const { return _name; }
	string getType() const { return _type; }
	int getHP() const;
	string getHPString() const { return "HP: " + to_string(_hitPoints) + "/" + to_string(hpMax); }
	float getHPPercent() const { return (_hitPoints * 100.f) / hpMax; }
	int getMP() const;
	int getCP() const;
	int getHPMax() const { return hpMax; }
	int getMPMax() const { return mpMax; }
	int getCPMax() const { return cpMax; }
	const Cell* getCell() const{ return _hisCell; }
	int getBonusDamage() const { return _bonusDamage; }
	Spell* getSpell(int spellID) const { return _spells.at(spellID); }
	bool hisTurn() const { return _myTurn; }
	virtual void displayBasic(ostream& o) const;
	bool isDead() const { return _dead; }
	map<int, Spell*> getSpells() const { return _spells; }

	/* every children have to implement those methods */
	// Attacks :
	virtual void basicAttack(Character & c) = 0;
	// cast a spell: Callback fonction
	virtual void cast(int spellID, void* data) = 0;
	// begin turn
	virtual void beginTurn();
	virtual void endTurn();

	// Movements : 
	// Il faut créer une méthode de pathfinding qui permettra de se déplacer de plus d'une case à la fois.
	bool move(int i, int j, bool moveWanted=true);
	bool move(Cell& c, bool moveWanted=true);
	bool move(unsigned int cell, bool moveWanted  = true);
	bool moveSingle(Cell& c, bool moveWanted = true);

	void actionCallback(int actionID, void*);
	void targetSelectorForCharacter(int spellIID, void* d = nullptr);
	void targetSelectorForCell(int , void* d = nullptr);
	void newCast(int spellID, void* target=nullptr);

	static const int BASIC_ATTACK = -1;
	static const int ACTION_MOVE = -2;
	static const int ACTION_ENDTURN = -3;

	/* TODO:: */
	/*virtual void update(){}
	virtual void initialize() {}*/

	friend ostream& operator<<(ostream& , const Character& );



	/* should return the selected target (by the user) (only in text mode) */
	void targetSelector(int spellID = 0, void* target = nullptr);
};

