#pragma once
#include "Button.h"

class Chrono :
	public Button
{
public:
	Chrono();
	virtual ~Chrono();
	virtual void update();
};

