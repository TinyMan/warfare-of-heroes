#include "Action.h"


Action::Action(Callback& cb, string t) : _text(t), _cb(cb)
{
}


Action::~Action()
{
}

void Action::trigger() const
{
	_cb.call(this->getData());
}

ostream& operator<<(ostream& o, const Action& a)
{
	o << a.getId() << ": " << a.getText() << endl;
	return o;
}