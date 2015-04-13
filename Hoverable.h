#pragma once
#include "MouseEventReceiver.h"
using namespace Events;

class Hoverable : public MouseEventReceiver
{
public:
	Hoverable();
	virtual ~Hoverable();

private:
	bool _hover = false;
};


