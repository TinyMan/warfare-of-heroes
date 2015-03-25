#include "UserInterface.h"

UserInterface::UserInterface()
{
}


UserInterface::~UserInterface()
{
}

void UserInterface::addAction( const Action & a)
{
	_actions.emplace(a.getId(), a);
}
ostream& operator<<(ostream& o, const UserInterface& ui) 
{
	o << "What do you want to do ?" << endl;
	for (auto& e : ui._actions)
	{
		o << e.second << endl;
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
	_actions.at(choice).trigger();
}