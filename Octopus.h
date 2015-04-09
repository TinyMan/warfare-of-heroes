#pragma once
#include <deque>
#include <sstream>
#include <SDL2/SDL.h>
#include "OctopusBaby.h"
#include "ServiceLocator.h"
using namespace std;

class Octopus
{
public:
	Octopus();
	virtual ~Octopus();

	virtual void render();
	virtual void update();

	virtual void initialize();
	virtual void updateWindowTitle();
private:
	/* collection of octopus babies */
	deque<OctopusBaby*> _babies;

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	stringstream _windowTitle;
	Uint32 _lastFpsUpdate = 0;
	Uint32 _fpsUpdateInterval = 1000; /* 1000 ms */
};

