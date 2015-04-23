#pragma once
#include "Label.h"
#include "Clickable.h"
#include "Hoverable.h"
class Button :
	public Label, public Clickable, public Hoverable
{
public:
	Button(int w, int h);
	virtual ~Button();
	virtual void update() {};
	virtual bool isInArea(SDL_Point) const;

	virtual bool isDirty() { return _dirty; }
	virtual void setDirty(bool d = true) { _dirty = d; }
	SDL_Color getColor() const { return _color; }
	void setColor(SDL_Color c) { _color = c; }
protected:
	void internalRender(SDL_Renderer* r, bool force = false);
private:
	bool _dirty = true;
	SDL_Color _color;
};

