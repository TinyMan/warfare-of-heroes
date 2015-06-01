#pragma once
#include <iostream>
#include "Font.h"
#include "Label.h"
using namespace std;

class Tooltip :
	public Label
{
public:
	// TODO: add default background image "Tooltip"
	Tooltip(int w, int h);
	virtual ~Tooltip();

	void setDirty(bool d = true) { _dirty = d; }
	bool isDirty() { return _dirty; }

	void setTitle(string title) { setIfDifferent(_title, title); }
	void setTitleColor(Color c) { setIfDifferent(_title_color, c); }
	void setTitleAlignment(Uint8 c) { setIfDifferent(_title_alignment, c); }
	void setTitleSize(Uint8 c) { setIfDifferent(_title_size, c); }

	// 2nd parameter: not yet supported
	void anchor(OctopusBaby* b, Uint8 alignment = Alignment::TOP | Alignment::LEFT);
	void anchor(OctopusBaby* b, int padding_x, int padding_y);
	void update(); // TODO: update position based on anchor
protected:
	virtual void internalRender(SDL_Renderer* r, bool force = false);

private:
	string _title;
	Uint8 _title_alignment = Alignment::TOP | Alignment::LEFT;
	Uint8 _title_size = 32;
	Color _title_color = Color::BLACK;

	bool _dirty = true;

	int _anchor_padding_x = 0;
	int _anchor_padding_y = 0;
	OctopusBaby * _anchored_to = nullptr;
};

