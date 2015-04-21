#include "Glyph.h"


Glyph::Glyph()
{
}


Glyph::~Glyph()
{
}

ostream& operator<<(ostream& o, const Glyph& g)
{
	o << "char id=" << g._id << " x=" << g._x << " y=" << g._y << " width=" << g._w << " height=" << g._h;
	return o;
}