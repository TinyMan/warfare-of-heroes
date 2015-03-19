#pragma once
#include <iostream>
#include "GameObject.h"

using namespace std;

class DeadObject :
	public GameObject
{
public:
	DeadObject();
	virtual ~DeadObject();

	/* TODO:: */
	/*virtual void update() { }
	virtual void initialize() {}*/
};

