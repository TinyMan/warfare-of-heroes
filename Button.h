#pragma once
#include "OctopusBaby.h"
#include "Clickable.h"
#include "Hoverable.h"
class Button :
	public OctopusBaby, public Clickable, public Hoverable
{
public:
	Button(SDL_Rect);
	Button(int x, int y, int w, int h);
	virtual ~Button();
	virtual void update() {};
	virtual void render(SDL_Renderer*);
	virtual bool isInArea(SDL_Point) const;

	virtual Button* getThis() { return this; }

protected:
	virtual void triggerModifyEvent();

private:
	SDL_Rect _rect;
};

