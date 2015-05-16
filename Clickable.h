#pragma once
#include "MouseEventReceiver.h"

using namespace Events;
using namespace MouseEvents;

class Clickable : public MouseEventReceiver
{
public:
	Clickable();
	virtual ~Clickable();

	virtual void onClick(ClickEvent* e){}
private:
	void internalOnClick(Event* e);

};
