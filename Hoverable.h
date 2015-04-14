#pragma once
#include "MouseEventReceiver.h"
#include "Modifiable.h"
using namespace Events;

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
		return (b && !_hover) || (!b && _hover);
	}
private:
	bool _hover = false;
};


