#pragma once
#include <iostream>
#include "GameObject.h"

using namespace std;

class Character : public GameObject
{
protected:
	string _name;
	int _hitPoints;
	int _movementPoints;
	int _capacityPoints;
	// Cell positionOnGrid;

public:
	Character(string name="NoName");
	virtual ~Character();

	// Setters :
	void lowerHitPoint(int amount);
	void removeMovementPoint(int amount=1);
	void removeCapaciyPoint(int amount=1);

	// Getters :
	int getHP();
	int getMP();
	int getCP();

	// Attacks :
	bool basicAttack(Character & c);

	// Movements :
	bool movement(); // Fran�ais : on met en param�tre la case et on v�rifie si on peut se d�placer 
	// Il faut cr�er une m�thode de pathfinding qui permettra de se d�placer de plus d'une case � la fois.

	virtual void update(){}
	virtual void initialize() {}
};

