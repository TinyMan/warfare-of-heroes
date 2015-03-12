#include "TimeService.h"
/*
TimeService::TimeService()
{
}


TimeService::~TimeService()
{
}

void TimeService::update()
{/*
	Uint32 t = SDL_GetTicks();
	while (_timeout.front().first <= t)
	{
		_timeout.front().second();
		_timeout.pop_front();
	}
}
/*
void TimeService::setTimeout(Uint32 t, Callback cb)
{
	t += SDL_GetTicks();
	if (_timeout.empty())
	{
		_timeout.emplace_back(t, cb);
	}
	else
	{
		list<pair<Uint32, Callback>>::iterator it = _timeout.begin();
		bool found = t <= it->first;
		while (!found && ++it != _timeout.end())
		{
			found = t <= it->first;
		}

		_timeout.insert(it, make_pair(t, cb));
	}
	display();

}*/