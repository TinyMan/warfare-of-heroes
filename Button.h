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
	virtual void update();
	virtual bool isInArea(SDL_Point) const;

	virtual bool isDirty() { return _dirty; }
	virtual void setDirty(bool d = true) { _dirty = d; }
	Color getColor() const { return _color; }
	void setColor(Color c) { Label::setIfDifferent(_color, c); }
	virtual void setBackground(const Texture& bg) { _regular_bg = bg; if (!hover()) Label::setBackground(bg); }
	virtual void setHoverBackground(const Texture& bg) { _hover_bg = bg; if (hover()) Label::setBackground(bg); }

	virtual void onMouseIn(MotionEvent* e) { Hoverable::onMouseIn(e); Label::setBackground(_hover_bg); }
	virtual void onMouseOut(MotionEvent* e) { Hoverable::onMouseOut(e); Label::setBackground(_regular_bg); }

	virtual void setEnabled(bool d = true) { Label::setIfDifferent(_enabled, d); }
	virtual bool isEnabled() const { return _enabled; }

	virtual Button* clone() const;
protected:
	void internalRender(SDL_Renderer* r, bool force = false);
	Texture _regular_bg;
	Texture _hover_bg;
private:
	bool _dirty = true;
	Color _color;
	bool _enabled = true;
};

