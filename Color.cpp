#include "Color.h"

const Color Color::BLACK = Color();
const Color Color::RED = Color(255,0,0);
const Color Color::GREEN = Color(0, 255, 0);
const Color Color::BLUE = Color(0, 0, 255);
const Color Color::TRANSPARENT = Color(0, 0, 0, 0);
const Color Color::WHITE = Color(255, 255, 255, 255);
const Color Color::FONTCOLOR = Color(190, 140);
const Color Color::BGCOLOR = Color(75, 60, 40);


Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	: _r(r), _g(g), _b(b), _a(a)
{
}


Color::~Color()
{
}


bool Color::operator == (const Color& c) const
{
	return c._r == _r && c._g == _g && c._b == _b && c._a == _a;
}
bool Color::operator != (const Color& c) const
{
	return !(c == *this);
}