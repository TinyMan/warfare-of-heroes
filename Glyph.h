#pragma once
#include <iostream>
#include <sstream>
using namespace std;
class Glyph
{
public:
	Glyph();
	virtual ~Glyph();
	void parse(string line);

	friend ostream& operator<<(ostream& o, const Glyph& g);
private:
	unsigned short _id = 0;
	unsigned short _x = 0;
	unsigned short _y = 0;
	unsigned short _w = 0;
	unsigned short _h = 0;
	short _x_offset = 0;
	short _y_offset = 0;
	short _x_advance = 0;
	unsigned short _page = 0;
	unsigned short _channel = 0;
	friend class Font;
};

