#pragma once
#include <deque>
#include <sstream>
#include <SDL2/SDL.h>
#include "OctopusBaby.h"
#include "ServiceLocator.h"
#include "Panel.h"
#include "Color.h"
#include "FontManager.h"
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
	void setFrame(Panel*, void* = nullptr);
	void setFrameAsync(Panel*);
	Panel* getFrame() const { return _frame; }

	SDL_Window* getWindow() const { return _window; }
	SDL_Renderer* getRenderer() const { return _renderer; }

	int getWWidth() const { return wWidth; }
	int getWHeight() const { return wHeight; }

private:
	Panel* _frame = nullptr;

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	stringstream _windowTitle;
	Uint32 _lastFpsUpdate = 0;
	Uint32 _fpsUpdateInterval = 1000; /* 1000 ms */
	int wWidth = 1200;
	int wHeight = 900;
};

