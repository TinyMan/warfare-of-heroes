#pragma once
#include <sstream>
#include <SDL2/SDL.h>
#include "OctopusBaby.h"
#include "ServiceLocator.h"
#include "MyContainer.h"
using namespace std;

class Octopus
	: public MyContainer<OctopusBaby*>
{
public:
	Octopus();
	virtual ~Octopus();

	virtual void render();
	virtual void update();

	virtual void initialize();
	virtual void updateWindowTitle();
	void addBaby(OctopusBaby*);
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	stringstream _windowTitle;
	Uint32 _lastFpsUpdate = 0;
	Uint32 _fpsUpdateInterval = 1000; /* 1000 ms */
};

