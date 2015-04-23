#pragma once
#include "Modifiable.h"
class Activable :
	public Modifiable
{
public:
	Activable();
	virtual ~Activable();

	virtual bool isActive() const { return _active; }
	virtual void setActive(bool b = true, void* = nullptr);
	bool operator<(const Activable& o);

private:
	bool _active = false;
};

