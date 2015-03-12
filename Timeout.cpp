#include "Timeout.h"
/*
int Timeout::_next_id = 0;

Timeout::Timeout(Uint32 t, Callback * cb) : _duration(t), _callback(cb), _trigger_time(SDL_GetTicks() + t), _id(_next_id++)
{
}
Timeout::~Timeout()
{
	delete _callback;
}
bool Timeout::check() const
{
	if (SDL_GetTicks() >= _trigger_time){
		//_callback();
		return true;
	}
	return false;
}
inline int Timeout::getId() const
{
	return _id;
}
inline Uint32 Timeout::getStartTime() const
{
	return _trigger_time - _duration;
}

inline Uint32 Timeout::getTriggerTime() const
{
	return _trigger_time;
}
inline bool Timeout::operator<=(const Timeout& t) const
{
	return _trigger_time <= t._trigger_time;
}*/