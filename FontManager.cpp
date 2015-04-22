#include "FontManager.h"
#include "ServiceLocator.h"

FontManager::FontManager()
{
}


FontManager::~FontManager()
{
}

string FontManager::loadFont(string filename)
{
	if (!filename.empty())
	{
		Font* f = new Font(filename);
		string name = f->getName();
		if (!name.empty())
		{
			_fonts[name] = f;
			return name;
		}
	}
	LOGERR << "Cannot load font from " << filename << endl;
	return "";
}

Font* FontManager::operator[](string fontName)
{
	if (_fonts.count(fontName) != 1)
		return nullptr;
	return _fonts[fontName];
}