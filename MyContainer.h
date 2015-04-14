#pragma once
#include <list>
#include "ActivableObject.h"
using namespace std;
using namespace Events;
template <class C>
class MyContainer
{
public:

	MyContainer()
	{
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
	virtual void onActivate(Event*)
	{
		_dirty = true;
		_nb_active++;
	}
	virtual void onDeactivate(Event*)
	{
		_dirty = true;
		if (_nb_active > 0) /* prevent silly errors */
			_nb_active--;
	}
	void update()
	{
		/* sorting the list of game objects */
		if (_dirty)
		{
			_list.sort();
			_dirty = false;
		}
	}
protected:
	list<C> _list;

private:
	bool _dirty = false;
	int _nb_active = 0;
};

