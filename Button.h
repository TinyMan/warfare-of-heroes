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
	virtual void render(SDL_Renderer*, bool dirty = false);
	virtual bool isInArea(SDL_Point) const;

	virtual bool isDirty() { return _dirty; }
	virtual void setDirty(bool d = true) { _dirty = d; }
	SDL_Color getColor() const { return _color; }
	void setColor(SDL_Color c) { _color = c; }

private:
	SDL_Rect _rect;
	bool _dirty = true;
	SDL_Color _color;
};

