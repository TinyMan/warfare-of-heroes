#pragma once
#include <iostream>
#include "GameObject.h"
#include "Game.h"

using namespace std;

class Cell;

/* abstract class */
class Character : public GameObject
{
protected:
	string _name;
	int _hitPoints;
	int _movementPoints;
	int _capacityPoints;
	int _damageOverTime = 0;
	int mpMax;
	int cpMax;
	Cell* _hisCell = nullptr;

public:
	Character(int x = 0, int y = 0, string name = "NoName");
	virtual ~Character();

	// Setters :
	void lowerHitPoint(int amount=0);
	void removeMovementPoint(int amount=1);
	void removeCapaciyPoint(int amount=1);
	void setDoT(int amount=0);

	// Getters :
	string getName() const { return _name; }
	int getHP() const;
	int getMP() const;
	int getCP() const;
	Cell* getCell() const { return _hisCell; }

	/* every children have to implement those methods */
	// Attacks :
	virtual void basicAttack(Character & c) = 0;
	// cast a spell: Callback fonction
	virtual void cast(int spellID, void* data) = 0;
	// begin turn
	virtual void beginTurn();
	virtual void endTurn(){};

	// Movements : 
	// Il faut créer une méthode de pathfinding qui permettra de se déplacer de plus d'une case à la fois.
	bool move(int i, int j, bool moveWanted=true);
	bool move(Cell& c, bool moveWanted=true);

	void actionCallback(int actionID, void*);
	void targetSelectorForCharacter(int spellIID, void* d = nullptr);
	void targetSelectorForCell(int , void* d = nullptr);

	static const int BASIC_ATTACK = -1;
	static const int ACTION_MOVE = -2;
	static const int ACTION_ENDTURN = -3;

	/* TODO:: */
	/*virtual void update(){}
	virtual void initialize() {}*/

	friend ostream& operator<<(ostream& , const Character& );
};

