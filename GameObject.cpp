#include "GameObject.h"

int GameObject::_next_id = 0;
int GameObject::_object_count = 0;

GameObject::GameObject() : _id(_next_id++)
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
		Events::Event* e;
		if (a)
			e = new ActivateEvent(this);
		else
			e = new DeactivateEvent(this);
		ServiceLocator::getEventService()->dispatch(e);
	}
}
void GameObject::setToDelete(bool a)
{
	if (_to_delete != a)
	{
		_to_delete = a;
		Events::Event* e;
		if (a){
			e = new ToDeleteEvent(this);
			ServiceLocator::getEventService()->dispatch(e);
		}
	}
}


/* TODO:: rename ... */
/* used only to sort */
bool compare(const GameObject* g, const GameObject* go)
{
//	ServiceLocator::getLogService()->info << "comparing " << g->getId() << " with " << go->getId() << endl;
	if (g->isActive() == go->isActive())
		return false;
	return g->isActive() && !go->isActive();
}
ostream& operator<<(ostream& o, const GameObject& go)
{
	o << "GameObject no. " << go.getId() << ": " << endl;
	o << "Active: " << go._active << endl;
	o << "To delete: " << go._to_delete << endl;
	return o;
}