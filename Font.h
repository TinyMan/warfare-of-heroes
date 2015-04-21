#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_img.h>
#include "Glyph.h"
#define MAX_GLYPHS 256
using namespace std;

class Font
{
public:
	Font(string name="", string fnt_filename = "", string atlas_filename = "");
	virtual ~Font();

	void parse(string filename = "");
	void parse(istream& s);

	void renderText(SDL_Renderer* r, string text);

	friend ostream& operator<<(ostream&, const Font&);
private:
	unsigned short _lineHeight = 0;
	unsigned short _base = 0;
	unsigned short _scale_width = 0;
	unsigned short _scale_height = 0;
	unsigned short _pages = 0;
	vector<Glyph> _glyphs;
	string _name;
	string _fntFilename = "";
	string _atlasFilename = "";
	SDL_Texture* _atlas;
};

