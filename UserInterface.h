#pragma once
#include <deque>
#include <iostream>
#include "Action.h"
using namespace Events;

class UserInterface
{
public:
	UserInterface();
	virtual ~UserInterface();
	
	virtual void addAction(const Action &);
	virtual Action getAction(int id) ;

	virtual void handleChoice(int choice);
	void clear() { _actions.clear(); }

	friend ostream& operator<<(ostream&, const UserInterface&);
private:
	deque<Action> _actions;
};

