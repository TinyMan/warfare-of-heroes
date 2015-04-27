#pragma once
#include <iostream>
#include "Font.h"
#include "Label.h"
using namespace std;

class Tooltip :
	public Label
{
public:
	Tooltip(int w, int h);
	virtual ~Tooltip();

	void setDirty(bool d = true) { _dirty = true; }
	bool isDirty() { return _dirty; }

	void setTitle(string title) { _title = title; setDirty(); }
private:
	string _title;
	Uint8 _title_alignment = Alignment::TOP | Alignment::LEFT;
	Uint8 _title_size = 32;

	bool _dirty = true;

};

