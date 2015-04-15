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
	virtual void beginFrame(){ _frameStart = SDL_GetTicks(); }
	virtual void endFrame() { _nbFrames++; }
	float getFps() const{ return _fps; }
	Uint32 getFrameTime() const { return _frameStart; }
	void updateFps();
	static Uint32 time() { return SDL_GetTicks(); }
private:
	list<Timeout*> _timeout;
	list<Interval*> _interval;

	Uint32 _frameStart = 0;
	Uint32 _nbFrames = 0;
	float _fps = 0;
	Uint32 _lastFpsUpdate = 0;
	Uint32 _fpsUpdateInterval = 1000; /* 1000 ms */
};

