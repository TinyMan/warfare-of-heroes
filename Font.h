#pragma once
#include <istream>
#include <vector>
#include <sstream>
#include "Glyph.h"
#define MAX_GLYPHS 256
using namespace std;

class Font
{
public:
	Font();
	virtual ~Font();

	void parse(istream& s);

private:
	unsigned short _lineHeight = 0;
	unsigned short _base = 0;
	unsigned short _scale_width = 0;
	unsigned short _scale_height = 0;
	unsigned short _pages = 0;
	vector<Glyph> _glyphs;
};

