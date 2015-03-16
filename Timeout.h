#pragma once
#include <iostream>
#include <SDL2/SDL_timer.h>
#include "Callback.h"

class Timeout
{
public:
	Timeout(Uint32 t, Callback & cb);
	~Timeout();

	int getId() const;
	Uint32 getStartTime() const;
	Uint32 getTriggerTime() const;

	/* return true if the timeout passed in parameter should be triggered after this */
	bool operator<=(const Timeout& t) const;

	bool check();	
	/* return wether the timeout is outdated/has been triggered */
	bool outDated() const;

private:
	int _id;
	/* how long is the timeout */
	Uint32 _duration;
	/* the time the timeout should be triggered */
	Uint32 _trigger_time;

	bool _triggered = false;

	Callback  _callback;

	static int _next_id;
};
