#pragma once
#include <SDL2/SDL_timer.h>
#include <iostream>
#include "Callback.h"

class Interval
{
public:
	Interval(Uint32 t, Callback& cb);
	~Interval();

	int getId() const;
	Uint32 getStartTime() const;	
	Uint32 getNextTriggerTime() const;

	bool check();

private:
	// calculate when is the next time we should trigger the callback function
	void updateNextTriggerTime();

	int _id;
	// the number of time the interval has triggered
	int _nb_triggered = 0;
	// the actual interval time
	Uint32 _interval;
	// the time the interval starts
	Uint32 _start_time;
	// the next time we should trigger the callback function
	Uint32 _next_trigger_time;

	Callback _callback;

	static int _next_id;
};
