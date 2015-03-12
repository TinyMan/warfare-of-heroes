#pragma once
#include <SDL2/SDL_timer.h>
#include "Callback.h"
/*
class Timeout
{
public:
	Timeout(Uint32 t, Callback * cb);
	~Timeout();

	int getId() const;
	Uint32 getStartTime() const;	
	Uint32 getTriggerTime() const;
	bool operator<=(const Timeout& t) const;

	bool check() const;	

private:
	int _id;
	Uint32 _duration;
	Uint32 _trigger_time;

	Callback * _callback;

	static int _next_id;
};
*/