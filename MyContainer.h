#pragma once
#include <list>
#include "ActivableObject.h"
#include "ServiceLocator.h"
#include "Modifiable.h"
using namespace std;
using namespace Events;

template <class C>
class MyContainer
{
public:

	MyContainer()
	{
		LOGINFO << "Instanciate " << this << " of type " << typeid(this).name() << endl;
		ServiceLocator::getEventService()->listen(typeid(Events::ModifyEvent), EventCallback(&MyContainer::onModify, this));
	}

	virtual ~MyContainer()
	{
	}

	void add(C g)
	{
		/* if it is active add it to te front */
		if (g->isActive())
		{
			_nb_active++;
			_list.push_front(g);
		}
		else /* else add it to the back */
			_list.push_back(g);
	}
	/*virtual void onActivate(Event*)
	{
		_unsorted = true;
		_dirty = true;
		_nb_active++;
	}
	virtual void onDeactivate(Event*)
	{
		_unsorted = true;
		_dirty = true;
		if (_nb_active > 0) // prevent silly errors 
			_nb_active--;
	}*/
	virtual void onModify(Event* e)
	{
		if (concernMe(e))
		{
			_dirty = true;
			LOGINFO << this << " is now DIRTY" << endl;
		}
		
	}
	void update()
	{
		/* sorting the list of game objects */
		if (_unsorted)
		{
			_list.sort();
			_unsorted = false;
		}
	}

	virtual bool concernMe(Event *e) const
	{
		//Modifiable* o = ((ModifyEvent*)e)->getObject();
		//LOGINFO << "testing if " << this << "(" << typeid(this).name() << ") contains " << o << "(" << TYPENAME(o) << ")" << endl;
		return contains((C)((ModifyEvent*)e)->getObject());
	}
	bool contains(C o) const
	{
		/* search if element is in _list */
		bool found = false;
		
		for (auto it = _list.begin(); it != _list.end(); ++it)
		{
			found = (*it == o);
			if (found)
				break;
		}
		if(found)
			LOGINFO << "FOUNNND!" << endl;
		return found;
	}
	bool isDirty() const { return _dirty; }
	void setDirty(bool d = true) { _dirty = d; }
protected:
	list<C> _list;

private:
	bool _unsorted = false;
	bool _dirty = true;
	int _nb_active = 0;
};

