#pragma once
#include <list>
#include "Modifiable.h"
#include "Activable.h"
#include "Sortable.h"
#include "ServiceLocator.h"

using namespace std;

/* 
The template argument MUST be inherited from Modifiable, Sortable classes
*/
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

	bool needSort()
	{
		for (auto it = _list.begin(); it != _list.end(); ++it)
		{
			_sorted = !((Sortable*)*it)->needSort();
			if (!_sorted)
				break;
		}
		return !_sorted;
	}
	void sort()
	{
		if (needSort())
		{
			_list.sort(::compare);
			for (Sortable * e : _list)
			{
				e->setSorted();
			}
			setSorted();
			setDirty();
		}
	}
	virtual void update()
	{
		sort();
	}
protected:
	list<T> _list;
	virtual void setSorted(bool b = true)
	{
		_sorted = b;
	}
private:
	bool _dirty;
	bool _sorted = true;
};

