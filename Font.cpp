#include "Font.h"


Font::Font(string filename, string fnt, string atlas)
	: _glyphs(MAX_GLYPHS), _name(filename)
{
	if (!_name.empty())
	{
		if (!fnt.empty())
			_fntFilename = fnt;
		if (!atlas.empty())
		{
			_atlasFilename = atlas;
			ServiceLocator::getTextureManager()->loadTexture(_atlasFilename, _name);
			_atlas = Texture((*ServiceLocator::getTextureManager())[_name]);
		}

		parse();
	}
}


Font::~Font()
{
}
void Font::parse(string filename)
{
	if (filename.empty())
	{
		filename = _fntFilename;
	}
	ifstream i;
	i.open(filename, ifstream::in);
	if (i.is_open())
	{
		parse(i);
	}
	else
		cerr << "Error openning " << filename << endl;
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
				{
					Converter >> CharID;
					_glyphs[CharID]._id = CharID;
				}
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
				else if (Key == "chnl")
					Converter >> _glyphs[CharID]._channel;
			}
		}
	}

}
void Font::renderText(SDL_Renderer* r, string text)
{
	SDL_Point cursor = { 0, 0 };
	for (char c : text)
	{
		Glyph ch = _glyphs[c];
		// Compute the source rect
		SDL_Rect src;
		src.x = ch._x;
		src.y = ch._y;
		src.w = ch._w;
		src.h = ch._h;

		// Compute the destination rect
		SDL_Rect dst;
		dst.x = cursor.x + ch._x_offset;
		dst.y = cursor.y + ch._y_offset;
		dst.w = ch._w;
		dst.h = ch._h;

		// Draw the image from the right texture
		//DrawRect(ch.page, src, dst);
		SDL_RenderCopy(r, _atlas, &src, &dst);
		LOGINFO << "Renderinf " << c << endl;
		// Update the position
		cursor.x += ch._x_advance;
	}
	
}
ostream& operator<<(ostream& o, const Font& f)
{
	o << "lineheight = " << f._lineHeight << endl;
	for (auto c : f._glyphs)
	{
		o << c << endl;
	}
	return o;	
}
