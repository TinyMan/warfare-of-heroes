#include "Action.h"


Action::Action(Callback& cb, string t, void* data) : _text(t), _cb(cb), Event(PLAYER_ACTION, data)
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
	o << a.getId() << ": " << a.getText() << " ";
	return o;
}