#include "Glyph.h"


Glyph::Glyph()
{
}


Glyph::~Glyph()
{
}

void Glyph::parse(string line)
{
	stringstream lineStream;
	string pair;
	string key, value;
	size_t i;
	lineStream << line;
	while (!lineStream.eof())
	{
		stringstream conv;
		lineStream >> pair;
		i = pair.find("=");
		key = pair.substr(0, i);
		value = pair.substr(i + 1);
		conv << value;

		if (key == "id")
			conv >> _id;
		else if (key == "x")
			conv >> _x;
		else if (key == "y")
			conv >> _y;
		else if (key == "width")
			conv >> _w;
		else if (key == "height")
			conv >> _h;
		else if (key == "xoffset")
			conv >> _x_offset;
		else if (key == "yoffset")
			conv >> _y_offset;
		else if (key == "xadvance")
			conv >> _x_advance;
		else if (key == "page")
			conv >> _page;
		else if (key == "chnl")
			conv >> _channel;
	}
}
ostream& operator<<(ostream& o, const Glyph& g)
{
	o << "char id=" << g._id << " x=" << g._x << " y=" << g._y << " width=" << g._w << " height=" << g._h;
	return o;
}