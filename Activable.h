#pragma once
#include "Modifiable.h"
class Activable :
	public Modifiable
{
public:
	Activable();
	virtual ~Activable();

	bool isActive() const { return _active; }
	void setActive(bool b = true);
	bool operator<(const Activable& o);

private:
	bool _active = false;
};

