#pragma once
#include <iostream>
#include "Cell.h"

using namespace std;

class Character
{
protected:
	string _name;
	int _hitPoints;
	int _movementPoints;
	int _capacityPoints;
	Cell positionOnGrid;

public:
	Character(string name="NoName");
	virtual ~Character();

	// Setters :
	void lowerHitPoint(int amount);
	void removeMovementPoint(int amount=1);
	void removeCapaciyPoint(int amount=1);

	// Getters :
	int getHP() const;
	int getMP() const;
	int getCP() const;
	Cell getCell() const;

	// Attacks :
	bool basicAttack(Character & c);

	// Movements :
	bool movement(); // Français : on met en paramètre la case et on vérifie si on peut se déplacer 
	// Il faut créer une méthode de pathfinding qui permettra de se déplacer de plus d'une case à la fois.
};

