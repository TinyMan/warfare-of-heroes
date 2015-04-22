#include "Label.h"


Label::Label(string text, Font* f)
	: _text(text), _font(f)
{
}

Label::Label(int x, int y, int w, int h, string text, Font* f)
	: OctopusBaby(x, y, w, h), _text(text), _font(f)
{

}
Label::~Label()
{
}

void Label::update()
{

}
void Label::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force | isDirty());
		if (d)
		{
			if (_font)
			{
				_font->renderText(r, _text, &_text_color, _text_size, &_rect, _alignment);
			}
		}
	}
}