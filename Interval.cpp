#include "Interval.h"

int Interval::_next_id = 0;

Interval::Interval(Uint32 t, Callback * cb) : _interval(t), _callback(cb), _id(_next_id++), _start_time(SDL_GetTicks())
{
	// calculate the first trigger time
	updateNextTriggerTime();
}
Interval::~Interval()
{
	delete _callback;
}
bool Interval::check()
{
	if (_next_trigger_time <= SDL_GetTicks())
	{
		_callback->call();
		// take note that we triggered the cb 1 more time
		_nb_triggered++;
		// need to update the trigger time only if it has changed
		updateNextTriggerTime();
	}
	return false;
}
int Interval::getId() const
{
	return _id;
}
Uint32 Interval::getStartTime() const
{
	return _start_time;
}

Uint32 Interval::getNextTriggerTime() const
{
	return _next_trigger_time;
}
void Interval::updateNextTriggerTime()
{
	_next_trigger_time = (_nb_triggered + 1) * _interval + _start_time;
}

