#include "Font.h"
#include "ServiceLocator.h"


Font::Font(string fnt)
	: _fntFilename(fnt)
{
	unsigned found = _fntFilename.find_last_of("/\\");
	_path_to_files = _fntFilename.substr(0, found+1);
	parse();
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
		LOGERR << "Error openning " << filename << endl;
	i.close();
	updateAtlases();
}
void Font::parse(std::istream& stream)
{
	string line;
	string lineType;
	size_t i;
	// until the end of the stream
	while (!stream.eof())
	{
		getline(stream, line);
		i = line.find(" ");
		lineType = line.substr(0, i);
		if (lineType == "info")
		{
			parseInfo(line);
		}
		else if (lineType == "common")
		{
			parseCommon(line);
		}
		else if (lineType == "page")
		{
			parsePages(line);
		}
		else if (lineType == "chars")
		{
			stringstream conv;
			i = line.find("count=") + 6;
			string val = line.substr(i);
			conv << val;
			conv >> _chars_count;
		}
		else if (lineType == "char")
		{
			parseChar(line);
		}
		else if (!line.empty())
		{
			LOGWARN << "Parsing font file: unknown line type" << endl;
		}
	}
}
void Font::renderText(SDL_Renderer* r, string text, Color* c, int size, SDL_Rect* rect, Uint8 a)
{
	if (c)
		setColor(*c);
	SDL_Point cursor = { 0, 0 };
	int initial_x = 0;
	if (rect)
	{
		initial_x = cursor.x = rect->x;
		cursor.y = rect->y;
		if (a == Alignment::UNKNOWN)
		{
			a = _alignment;
		}		
		if (a & Alignment::CENTERY)
		{
			cursor.y += (rect->h / 2) - (getPixelHeight(text, size) / 2);
		}
		else if (!(a & Alignment::TOP))
		{
			cursor.y += rect->h - getPixelHeight(text, size);
		}
		
	}
	float coef = (float)size / _original_size;
	bool newline = true;
	size_t i = 0;
	for (char c : text)
	{
		if (newline)
		{
			if (a & Alignment::CENTERX)
			{
				cursor.x += (rect->w / 2) - (getPixelLength(text.substr(i, text.find('\n', i)), size) / 2);
			}
			else if (!(a & Alignment::LEFT))
			{
				cursor.x += rect->w - getPixelLength(text.substr(i, text.find('\n', i)), size);
			}
			newline = false;
		}
		if (_glyphs.count(c) == 1)
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
			dst.x = cursor.x + int(ch._x_offset*coef);
			dst.y = cursor.y + int(ch._y_offset*coef);
			dst.w = int(ch._w*coef);
			dst.h = int(ch._h*coef);

			// Draw the image from the right texture
			//DrawRect(ch.page, src, dst);
			SDL_RenderCopy(r, _pages[ch._page], &src, &dst);
			// Update the position
			cursor.x += int(ch._x_advance*coef);
		}
		if (c == '\n')
		{
			cursor.y += int(_lineHeight*coef);
			cursor.x = initial_x;
			newline = true;
		}
		i++;
	}
	
}
ostream& operator<<(ostream& o, const Font& f)
{
	o << "lineheight = " << f._lineHeight << endl;
	for (auto c : f._glyphs)
	{
		o << c.second << endl;
	}
	return o;	
}

void Font::parseChar(string line)
{
	stringstream lineStream;
	string pair;
	string key, value;
	size_t i;
	lineStream << line;
	int charID;
	while (!lineStream.eof())
	{
		stringstream conv;
		lineStream >> pair;
		i = pair.find("=");
		key = pair.substr(0, i);
		value = pair.substr(i + 1);
		conv << value;
		if (key == "id")
		{
			conv >> charID;
			_glyphs[charID].parse(line);
			break;
		}
	}
}
void Font::parseCommon(string line)
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
		if (key == "lineHeight")
			conv >> _lineHeight;
		else if (key == "base")
			conv >> _base;
		else if (key == "scaleW")
			conv >> _scale_width;
		else if (key == "scaleH")
			conv >> _scale_height;
		else if (key == "pages")
			conv >> _pages_count;
		else if (key == "packed")
			conv >> _packed;
		else if (key == "alphaChnl")
			conv >> _alpha_chnl;
		else if (key == "redChnl")
			conv >> _red_chnl;
		else if (key == "greenChnl")
			conv >> _green_chnl;
		else if (key == "blueChnl")
			conv >> _blue_chnl;

	}
	_pages_filename.resize(_pages_count);
	_pages.resize(_pages_count);
}
void Font::parseInfo(string line)
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
		
		if (key == "face")
		{
			i = line.find("face=\"")+6;
			pair = line.substr(i);
			i = pair.find('\"');
			_name = pair.substr(0, i);
		}
		else if (key == "size")
			conv >> _original_size;
	}
}
void Font::parsePages(string line)
{
	stringstream lineStream;
	string pair;
	string key, value;
	size_t i;
	unsigned short pageId = 0;
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
			conv >> pageId;
		else if (key == "file")
		{
			conv >> pair;
			pair.erase(
				remove(pair.begin(), pair.end(), '\"'),
				pair.end()
				);

			_pages_filename[pageId] = _path_to_files + pair;
		}
	}

}
void Font::updateAtlases()
{
	for (unsigned short i = 0; i < _pages_filename.size(); i++)
	{
		ServiceLocator::getTextureManager()->loadTexture(_pages_filename[i]);
		_pages[i] = (*ServiceLocator::getTextureManager())[_pages_filename[i]];
	}
}
void Font::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	for (auto e : _pages)
	{
		SDL_SetTextureColorMod(e, r, g, b);
	}
}
int Font::getPixelLength(string text, int size)
{
	//LOGINFO << "Getting pixel length of text " << text << " with size " << size << endl;
	int s = 0;
	float coef = (float)size / _original_size;
	for (char c : text)
	{
		s += int(_glyphs[c]._x_advance*coef);
	}
	//LOGINFO << "Size = " << s << endl;
	return s;
}
int Font::getPixelHeight(string text, int size)
{
	int s = _lineHeight;
	float coef = (float)size / _original_size;
	s *= int(coef * (count(text.begin(), text.end(), '\n') + 1));
	return s;
}