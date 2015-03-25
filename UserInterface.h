#pragma once
#include <map>
#include <iostream>
#include "Action.h"

class UserInterface
{
public:
	UserInterface();
	virtual ~UserInterface();
	
	virtual void addAction(const Action &);
	virtual void display() const;
	virtual Action getAction(int id) ;

private:
	map<int, Action> _actions;
};

