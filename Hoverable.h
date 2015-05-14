#pragma once
#include "MouseEventReceiver.h"
#include "Modifiable.h"
using namespace Events;
using namespace MouseEvents;

class Tooltip;

class Hoverable 
	: public MouseEventReceiver, public Modifiable
{
public:
	Hoverable();
	virtual ~Hoverable();

	bool hover() const { return _hover; }
	void setHover(bool h = true) { _hover = h; }

	virtual bool concernMe(Event* e) const
	{
		bool b = MouseEventReceiver::concernMe(e);
		if (!_notify_each_move)
			return (b && !_hover) || (!b && _hover); // mouse in or mouse out
		else
			return b;
	}
	virtual void onMouseIn(MouseEvents::MotionEvent* e);
	virtual void onMouseOut(MouseEvents::MotionEvent* e);
	virtual void onMouseMove(MouseEvents::MotionEvent* e);

	void setEveryMovesNotification(bool d = true) { _notify_each_move = d; }
	bool getEveryMovesNotification() const { return _notify_each_move; }

private:
	bool _hover = false;
	bool _notify_each_move = false;
};


