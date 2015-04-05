#include "UserInterface.h"

UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}

void UserInterface::addAction( const Action & a)
{
	_actions.push_front(a);
}
ostream& operator<<(ostream& o, const UserInterface& ui) 
{
	o << "What do you want to do ?" << endl;
	int i = 0;
	for (auto& e : ui._actions)
	{
		o << i++ << ": " << e << endl;
	}
	o << "Enter your choice: " << flush;
	return o;
}
Action UserInterface::getAction(int id) 
{
	return _actions.at(id);
}
void UserInterface::handleChoice(int choice)
{
	if (choice < (int)_actions.size() && choice >= 0)
		_actions.at(choice).trigger();
}