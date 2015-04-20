#include "Font.h"


Font::Font()
	: _glyphs(MAX_GLYPHS)
{
}


Font::~Font()
{
}

void Font::parse(std::istream& Stream)
{
	string Line;
	string Read, Key, Value;
	std::size_t i;
	while (!Stream.eof())
	{
		std::stringstream LineStream;
		std::getline(Stream, Line);
		LineStream << Line;

		//read the line's type
		LineStream >> Read;
		if (Read == "common")
		{
			//this holds common data
			while (!LineStream.eof())
			{
				std::stringstream Converter;
				LineStream >> Read;
				i = Read.find('=');
				Key = Read.substr(0, i);
				Value = Read.substr(i + 1);

				//assign the correct value
				Converter << Value;
				if (Key == "lineHeight")
					Converter >> _lineHeight;
				else if (Key == "base")
					Converter >> _base;
				else if (Key == "scaleW")
					Converter >> _scale_width;
				else if (Key == "scaleH")
					Converter >> _scale_height;
				else if (Key == "pages")
					Converter >> _pages;
			}
		}
		else if (Read == "char")
		{
			//this is data for a specific char
			unsigned short CharID = 0;

			while (!LineStream.eof())
			{
				std::stringstream Converter;
				LineStream >> Read;
				i = Read.find('=');
				Key = Read.substr(0, i);
				Value = Read.substr(i + 1);

				//assign the correct value
				Converter << Value;
				if (Key == "id")
					Converter >> CharID;
				else if (Key == "x")
					Converter >> _glyphs[CharID]._x;
				else if (Key == "y")
					Converter >> _glyphs[CharID]._y;
				else if (Key == "width")
					Converter >> _glyphs[CharID]._w;
				else if (Key == "height")
					Converter >> _glyphs[CharID]._h;
				else if (Key == "xoffset")
					Converter >> _glyphs[CharID]._x_offset;
				else if (Key == "yoffset")
					Converter >> _glyphs[CharID]._y_offset;
				else if (Key == "xadvance")
					Converter >> _glyphs[CharID]._x_advance;
				else if (Key == "page")
					Converter >> _glyphs[CharID]._page;
			}
		}
	}

}
