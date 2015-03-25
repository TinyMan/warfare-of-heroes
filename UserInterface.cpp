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
void UserInterface::display() const
{

}
Action UserInterface::getAction(int id) 
{
	return _actions.at(id);
}