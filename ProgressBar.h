#pragma once
#include "OctopusBaby.h"
class ProgressBar :
	public OctopusBaby
{
public:
	ProgressBar();
	ProgressBar(int w, int h);
	virtual ~ProgressBar();
	void setValue(float v) { _value = v; setDirty(); }

	virtual void setDirty(bool d = true) { _dirty = d; }
	virtual bool isDirty() { return _dirty; }
	virtual void update();

	void setColor(Color c) { _foreground_color = c; setDirty(); }
	void setBorderColor(Color c) { _border_color = c; setDirty(); }

protected:
	void internalRender(SDL_Renderer* r, bool force = false);

private:
	bool _dirty = true;
	float _value = 100;
	Color _foreground_color = Color::GREEN;
	Color _border_color = Color::BLACK;
};

