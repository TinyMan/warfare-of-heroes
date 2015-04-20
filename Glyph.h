#pragma once
class Glyph
{
public:
	Glyph();
	virtual ~Glyph();

private:
	unsigned short _x = 0;
	unsigned short _y = 0;
	unsigned short _w = 0;
	unsigned short _h = 0;
	float _x_offset = 0;
	float _y_offset = 0;
	float _x_advance = 0;
	unsigned short _page = 0;
	friend class Font;
};

