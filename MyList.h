#pragma once
#include <list>
#include "Modifiable.h"
#include "Activable.h"
using namespace std;
template<class T>
class MyList :
	public Modifiable
{
public:

	MyList()
	{
	}

	virtual ~MyList()
	{
	}

	void add(T o)
	{
		_list.push_back(o);
		setDirty();
	}
	virtual bool isDirty()
	{
		for (auto it = _list.begin(); it != _list.end(); ++it)
		{
			_dirty |= (*it)->isDirty();
			if (_dirty)
				break;
		}

		return _dirty;
		
	}
	bool contains(T o) const
	{
		/* search if element is in _list */
		bool found = false;

		for (auto it = _list.begin(); it != _list.end(); ++it)
		{
			found = (*it == o);
			if (found)
				break;
		}
		return found;
	}
	list<T> * getList() { return &_list; }
	virtual void setDirty(bool b = true) { _dirty = b; }
private:
	list<T> _list;
	bool _dirty;
};

