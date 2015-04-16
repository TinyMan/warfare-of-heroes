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
	if (_list.isDirty())
	{
		//LOGINFO << "Rendering mother of octopus ! " << endl;
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
		SDL_RenderClear(_renderer);

		for (auto ob : *_list.getList())
		{
			ob->render(_renderer, true);
		}
		_list.setDirty(false);
	}
	SDL_RenderPresent(_renderer);
	updateWindowTitle();	
}
void Octopus::update()
{
	for (auto o : *_list.getList())
	{
		o->update();
	}
	_list.update();
	
}
void Octopus::initialize()
{
	_window = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wWidth, wHeight, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	ServiceLocator::provide(new TextureManager(_renderer));
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
		//_babies.push_back(b);
		_list.add(b);
	}
}