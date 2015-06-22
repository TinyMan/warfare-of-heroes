#include "Label.h"
#include "ServiceLocator.h"

Label::Label(string text, Font* f)
	: _text(text), _font(f)
{
}

Label::Label(int w, int h, string text, Font* f, int x, int y)
	: OctopusBaby(x, y, w, h), _text(text), _font(f)
{
	if (f == nullptr)
		_font = (*ServiceLocator::getFontManager())["LifeCraft"];
	setTextColor(Color::FONTCOLOR);
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
				_font->renderText(r, _text, &_text_color, _text_size, &_text_rect, _alignment);
			}
		}
	}
}
void Label::updateAbsoluteRect()
{
	OctopusBaby::updateAbsoluteRect();
	_text_rect = _relative_rect;
	_text_rect.x = _padding_left;
	_text_rect.y = _padding_top;
	_text_rect.w -= _padding_right;
	_text_rect.h -= _padding_bottom;
	
}

void Label::setPadding(int left, int top, int right, int bottom)
{
	_padding_left = left;
	_padding_top = top;
	_padding_right = right;
	_padding_bottom = bottom;
	setDirty();
}
Label* Label::clone() const
{
	// BROKEN
	Label * l = new Label(*this);
	return l;
}