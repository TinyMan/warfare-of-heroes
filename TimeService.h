#pragma once
#include <SDL2/SDL_Timer.h>
#include <list>
#include <utility>
#include <algorithm>
#include <iostream>
#include "Callback.h"
#include "Timeout.h"
#include "Interval.h"

using namespace std;

class TimeService
{
public:
	TimeService();
	virtual ~TimeService();

	virtual void setTimeout(Uint32 t, Callback&  callback);
	virtual void setInterval(Uint32 t, Callback& callback);
	virtual void update();
	virtual void display()
	{
		for (auto e : _timeout)
		{
			cout << "Timeout no." << e->getId() << ": " << e->getTriggerTime() << endl;
		}
		cout << "-----------" << endl;
		for (auto e : _interval)
		{
			cout << "Interval no. " << e->getId() << ": " << e->getNextTriggerTime() << endl;
		}
		cout << "-----------" << endl;
	}
private:
	list<Timeout*> _timeout;
	list<Interval*> _interval;
};

