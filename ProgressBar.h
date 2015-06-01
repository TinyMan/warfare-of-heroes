#pragma once
#include "OctopusBaby.h"
class ProgressBar :
	public OctopusBaby
{
public:
	ProgressBar();
	ProgressBar(int w, int h);
	virtual ~ProgressBar();
	void setValue(float v) { setIfDifferent(_value, v); }

	virtual void setDirty(bool d = true) { _dirty = d; }
	virtual bool isDirty() { return _dirty; }
	virtual void update();

	void setColor(Color c) { setIfDifferent(_foreground_color, c); }
	void setBorderColor(Color c) { setIfDifferent(_border_color, c); }

protected:
	void internalRender(SDL_Renderer* r, bool force = false);

private:
	bool _dirty = true;
	float _value = 100;
	Color _foreground_color = Color::GREEN;
	Color _border_color = Color::BLACK;
};

