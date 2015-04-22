#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Glyph.h"
#include "Texture.h"
#include "Color.h"
#define MAX_GLYPHS 256
using namespace std;

class Font
{
public:
	Font(string fnt_filename = "");
	virtual ~Font();

	void parse(string filename = "");
	void parse(istream& s);

	void renderText(SDL_Renderer* r, string text, Color* c= nullptr, int size = 32);
	void setColor(Color c) { setColor(c.r(), c.g(), c.b()); }
	void setColor(Uint8 r, Uint8 g, Uint8 b);
	friend ostream& operator<<(ostream&, const Font&);

	string getName() const { return _name; }
private:
	string _fntFilename = "";
	string _path_to_files = "";

	/* info */
	string _name;
	unsigned short _original_size = 0;

	/* common */
	unsigned short _lineHeight = 0;
	unsigned short _base = 0;
	unsigned short _scale_width = 0;
	unsigned short _scale_height = 0;
	unsigned short _pages_count = 0;
	bool _packed = false;
	unsigned short _alpha_chnl = 0;
	unsigned short  _red_chnl = 0;
	unsigned short _green_chnl = 0;
	unsigned short _blue_chnl = 0;
	
	/* pages */
	vector<string> _pages_filename;
	vector<Texture> _pages;

	/* chars */
	unsigned short _chars_count;
	map<unsigned short, Glyph> _glyphs;

	void parseInfo(string infoLine);
	void parseCommon(string commonLine);
	void parsePages(string pageLine);
	void parseChar(string charLine);
	void updateAtlases();
};

