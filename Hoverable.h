#pragma once
#include "MouseEventReceiver.h"
using namespace Events;

class Hoverable : public MouseEventReceiver
{
public:
	Hoverable();
	virtual ~Hoverable();

	bool hover() const { return _hover; }
	void setHover(bool h = true) { _hover = h; }

	virtual bool concernMe(Event* e) const
	{
		return (MouseEventReceiver::concernMe(e) && !_hover) || _hover;
	}
private:
	bool _hover = false;
};


