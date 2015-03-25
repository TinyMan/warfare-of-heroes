#pragma once
#include <deque>
#include <iostream>
#include "Action.h"

class UserInterface
{
public:
	UserInterface();
	virtual ~UserInterface();
	
	virtual void addAction(const Action &);
	virtual Action getAction(int id) ;

	virtual void handleChoice(int choice);

	friend ostream& operator<<(ostream&, const UserInterface&);
private:
	deque<Action> _actions;
};

