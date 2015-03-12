#pragma once
#include <SDL2/SDL_Timer.h>
#include <list>
#include <utility>
#include <algorithm>
#include <iostream>
#include "Callback.h"

using namespace std;
/*
class TimeService
{
public:
	TimeService();
	virtual ~TimeService();

	virtual void setTimeout(Uint32 t, Callback callback);
	virtual void update();
	virtual void display()
	{
		for (auto e : _timeout)
		{
			cout << e.first  << endl;
		}
		cout << "-----------" << endl;
	}
private:
	list<pair<Uint32 , Callback>> _timeout;
	list<pair<Uint32, Callback>> _interval;
};

*/