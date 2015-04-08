#pragma once
#include <deque>
#include <SDL2/SDL.h>
#include "OctopusBaby.h"
using namespace std;

class Octopus
{
public:
	Octopus();
	virtual ~Octopus();

	virtual void render();
	virtual void update();

	virtual void initialize();

private:
	/* collection of octopus babies */
	deque<OctopusBaby*> _babies;

	SDL_Window* _window;
	SDL_Renderer* _renderer;
};

