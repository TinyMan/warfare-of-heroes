#pragma once
#include <iostream>
#include "GameObject.h"

using namespace std;

class DeadObject :
	public GameObject
{
public:
	DeadObject(Game*);
	virtual ~DeadObject();

	virtual void update() = 0;
	virtual void initialize() = 0;
};

