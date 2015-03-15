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

	virtual void update() { cout << "hello from " << getId() << endl; GameObject::update(); }
	virtual void initialize() {}
};

