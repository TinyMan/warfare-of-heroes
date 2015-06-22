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
	SDL_DisplayMode dm;
	if (SDL_GetDesktopDisplayMode(0, &dm) == 0) {
		if (dm.w > 1200 && dm.h > 900)
		{
			wWidth = 1200;
			wHeight = 900;
		}
		else if (dm.w > 800 && dm.h > 600)
		{
			wWidth = 800;
			wHeight = 600;
		}
		else
		{
			wWidth = 400;
			wHeight = 300;
		}
			
	}
	_window = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wWidth, wHeight, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderSetLogicalSize(_renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT);
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