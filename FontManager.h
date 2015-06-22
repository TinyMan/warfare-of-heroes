#pragma once
#include <iostream>
#include "Font.h"
using namespace std;
class FontManager
{
public:
	FontManager();
	virtual ~FontManager();

	// return the font name
	string loadFont(string filename);

	Font* operator[](string fontName);
private:
	map<string, Font*> _fonts;
};

