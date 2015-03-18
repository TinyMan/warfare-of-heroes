#include "GameObject.h"

int GameObject::_next_id = 0;
int GameObject::_object_count = 0;

GameObject::GameObject(Game* inst) : _id(_next_id++), _gameInstance(inst)
{
	_object_count++;
}


GameObject::~GameObject()
{
	_object_count--;
}

void GameObject::setActive(bool a)
{
	if (_active != a)
	{
		_active = a;
		ServiceLocator::getEventService()->dispatch(Event(a ? Event::GAMEOBJECT_ACTIVATE : Event::GAMEOBJECT_DEACTIVATE, this));
	}
}
