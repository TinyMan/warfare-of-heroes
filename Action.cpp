#include "Action.h"


namespace Events{
	Action::Action(Callback& cb, string t) : _text(t), _cb(cb)
	{
	}


	Action::~Action()
	{
	}

	void Action::trigger() const
	{
		_cb.call();
	}

	ostream& operator<<(ostream& o, const Action& a)
	{
		o << a.getText() << " ";
		return o;
	}
}