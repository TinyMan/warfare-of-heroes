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
	if (_frame)
	{
		_frame->render(_renderer);
	}
	SDL_RenderPresent(_renderer);
	updateWindowTitle();	
}
void Octopus::update()
{
	if(_frame)
		_frame->update();
}
void Octopus::initialize()
{
	_window = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wWidth, wHeight, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
	ServiceLocator::provide(new TextureManager(_renderer));
	ServiceLocator::provide(new FontManager());
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
void Octopus::setFrame(Panel* b, void*)
{
	if (b)
	{
		//LOGINFO << "Changing frame" << endl;
		//_babies.push_back(b);
		_frame = b;
		b->setActive(true);
	}
}
void Octopus::setFrameAsync(Panel* to)
{
	_frame->setActive(false);
	ServiceLocator::getTimeService()->setTimeout(1, Callback(&Octopus::setFrame, this, to));
}