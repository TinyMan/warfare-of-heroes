#pragma once
#include <iostream>
#include "GameObject.h"

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
	Cell* _hisCell = nullptr;

public:
	Character(string name="NoName");
	virtual ~Character();

	// Setters :
	void lowerHitPoint(int amount);
	void removeMovementPoint(int amount=1);
	void removeCapaciyPoint(int amount=1);

	// Getters :
	string getName() const { return _name; }
	int getHP() const;
	int getMP() const;
	int getCP() const;
	Cell* getCell() const { return _hisCell; }

	/* every children have to implement those methods */
	// Attacks :
	virtual bool basicAttack(Character & c) = 0;
	// cast a spell
	virtual bool cast(int spellID, void* data) = 0;

	// Movements :
	bool movement(); // Fran�ais : on met en param�tre la case et on v�rifie si on peut se d�placer 
	// Il faut cr�er une m�thode de pathfinding qui permettra de se d�placer de plus d'une case � la fois.
	bool move(int i, int j);

	/* TODO:: */
	/*virtual void update(){}
	virtual void initialize() {}*/
};

