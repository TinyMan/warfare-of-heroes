#pragma once
#include "OctopusBaby.h"
#include "Clickable.h"
class Button :
	public OctopusBaby, public Clickable
{
public:
	Button(SDL_Rect);
	Button(int x, int y, int w, int h);
	virtual ~Button();
	virtual void update() {};
	virtual void render(SDL_Renderer*);
	virtual bool isInArea(SDL_Point) const;
private:
	SDL_Rect _rect;
};

