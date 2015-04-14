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

	virtual bool isDirty() { return _dirty; }
	virtual void setDirty(bool d = true) { _dirty = d; }

protected:
	virtual void internalRender(SDL_Renderer* r);
private:
	SDL_Rect _rect;
	bool _dirty = true;
};

