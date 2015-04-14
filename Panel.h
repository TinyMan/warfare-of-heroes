#pragma once
#include <SDL2/SDL.h>
#include "OctopusBaby.h"
#include "MyContainer.h"
class Panel :
	public OctopusBaby, public MyContainer<OctopusBaby*>
{
public:
	Panel(SDL_Renderer* r, SDL_Rect rect);
	Panel(SDL_Renderer* r, int x = 0, int y = 0, int w = 0, int h = 0);
	virtual ~Panel();

	virtual void render(SDL_Renderer*);
	virtual void update(){}

	virtual Panel* getThis() { return this; }

protected:
	virtual void internalRender(SDL_Renderer* r);
	virtual void triggerModifyEvent();

private:
	SDL_Rect _rect;
	SDL_Texture* _texture;

	void initialize(SDL_Renderer* r);
};

