#include "Octopus.h"


Octopus::Octopus()
{
}


Octopus::~Octopus()
{
	SDL_DestroyWindow(_window);
}

void Octopus::render()
{
	//LOGINFO << "Rendering mother of octopus ! " << endl;
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
	SDL_RenderClear(_renderer);
	//SDL_FillRect(NULL, NULL, 0);
	for (auto ob : _list)
	{
		ob->render(_renderer);
	}
	SDL_RenderPresent(_renderer);
	updateWindowTitle();
	
}
void Octopus::update()
{

}
void Octopus::initialize()
{
	_window = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 900, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}
void Octopus::updateWindowTitle()
{
	Uint32 now = TIMESERVICE->time();
	if (now - _lastFpsUpdate > _fpsUpdateInterval)
	{
		TIMESERVICE->updateFps();
		stringstream s;
		s << TIMESERVICE->getFps() << " fps";
		SDL_SetWindowTitle(_window, s.str().c_str());
		_lastFpsUpdate = now;
	}
}
void Octopus::addBaby(OctopusBaby* b)
{
	if (b)
	{
		LOGINFO << "Adding octopus baby" << endl;
		add(b);
	}
}