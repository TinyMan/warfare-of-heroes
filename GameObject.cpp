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


/* used only to sort */
bool GameObject::compare(const Sortable* g) const
{
//	ServiceLocator::getLogService()->info << "comparing " << g->getId() << " with " << go->getId() << endl;
	GameObject* go = (GameObject*)g;
	if (isActive() == go->isActive())
		return false;
	return isActive() && !go->isActive();
}
ostream& operator<<(ostream& o, const GameObject& go)
{
	o << "GameObject no. " << go.getId() << ": " << endl;
	o << "Active: " << go._active << endl;
	o << "To delete: " << go._to_delete << endl;
	return o;
}