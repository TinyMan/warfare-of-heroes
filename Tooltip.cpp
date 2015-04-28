#include "Tooltip.h"
#include "Hoverable.h"

Tooltip::Tooltip(int w, int h)
	: Label(w, h)
{
	setFont((*ServiceLocator::getFontManager())["Comic Sans MS"]);
}


Tooltip::~Tooltip()
{
}

void Tooltip::anchor(OctopusBaby* b, Uint8 align)
{
	if (b)
	{
		_anchored_to = b;
	}
}
void Tooltip::anchor(OctopusBaby* b, int padding_x, int padding_y)
{
	anchor(b);
	_anchor_padding_x = padding_x;
	_anchor_padding_y = padding_y;
}
void Tooltip::update()
{
	Label::update();
	if (_anchored_to && _anchored_to->isDirty())
	{
		SDL_Rect _anchor_absolute_rect = _anchored_to->getAbsolutRect();
		_relative_rect.y = _anchor_absolute_rect.y - _container_rect.y - _relative_rect.h + _anchor_padding_y;
		_relative_rect.x = _anchor_absolute_rect.x - _container_rect.x + _anchor_padding_x;

		updateAbsoluteRect();
		if (Hoverable* h = dynamic_cast<Hoverable*>(_anchored_to))
		{
			setActive(h->hover());
		}
		else
			setActive(false);
	}
}
void Tooltip::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force | isDirty());
		if (d)
		{
			_font->renderText(r, _title, &_title_color, _title_size, &_relative_rect, _title_alignment);
		}
		Label::internalRender(r, d);
	}
}