#include "TimeService.h"
#include "ServiceLocator.h"

TimeService::TimeService()
{
}


TimeService::~TimeService()
{
	for (auto e : _timeout)
		delete e;
	for (auto e:_interval)
		delete e;
}

void TimeService::update()
{	
	// trigger the first timeout, stop when the first timeout is not triggered
	// since the list is sorted if the first doesn't trigger neither will the others
	while (!_timeout.empty() && _timeout.front()->check())
	{
		delete _timeout.front();
		//cout << "Triggered timeout no. " << _timeout.front().getId() << endl;		
		_timeout.pop_front();
	}
	for (auto e : _interval)
	{
		e->check();
	}
}

void TimeService::setTimeout(Uint32 t, Callback& cb)
{
	// if it is the first timeout we add
	if (_timeout.empty())
	{
		_timeout.push_back(new Timeout(t, cb));
	}
	else // else we insert the timeout where it should be on the sorted list
	{
		Timeout * new_timeout = new Timeout(t, cb);
		// search the good position
		list<Timeout*>::iterator it = _timeout.begin();
		bool found = *new_timeout <= **it;
		while (!found && ++it != _timeout.end())
		{
			found = *new_timeout <= **it;
		}

		// insert it
		_timeout.insert(it, new_timeout);
	}
	//display();
}
void TimeService::setInterval(Uint32 t, Callback& cb)
{
	_interval.push_back(new Interval(t, cb));
	
	//display();
}
void TimeService::updateFps()
{
	Uint32 t = time();
	Uint32 delta = t - _lastFpsUpdate;
	if (delta > _fpsUpdateInterval)
	{
		//LOGINFO << "Updating fps count" << endl;
		_fps = (float)_nbFrames / (delta / 1000.f);
		_nbFrames = 0;
		_lastFpsUpdate = t;
	}
}