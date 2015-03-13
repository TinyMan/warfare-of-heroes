#include "Timeout.h"

int Timeout::_next_id = 0;

Timeout::Timeout(Uint32 t, Callback&  cb) : _duration(t), _callback(cb), _trigger_time(SDL_GetTicks() + t), _id(_next_id++)
{
}
Timeout::~Timeout()
{
	cout << "Timeout no. " << _id << " dying" << endl;
}
bool Timeout::check()
{
	if (!_triggered && SDL_GetTicks() >= _trigger_time){
		_callback.call();
		_triggered = true;
		return true;
	}
	return false;
}
int Timeout::getId() const
{
	return _id;
}
Uint32 Timeout::getStartTime() const
{
	return _trigger_time - _duration;
}

Uint32 Timeout::getTriggerTime() const
{
	return _trigger_time;
}
bool Timeout::operator<=(const Timeout& t) const
{
	return _trigger_time <= t._trigger_time;
}
bool Timeout::outDated() const
{
	return _triggered;
}