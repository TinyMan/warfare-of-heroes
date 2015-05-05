#include "Button.h"
#include "EventCallback.h"
#include "Game.h"

Button::Button(int w, int h) 
	: Label(w, h), _regular_bg(w, h, Color::RED), _hover_bg(w, h, Color::BLUE)
{
	_color = { 255, 0, 0, 255 };
	setFont((*ServiceLocator::getFontManager())["LifeCraft"]);
	Label::setBackground(_regular_bg);
}


Button::~Button()
{
}


bool Button::isInArea(SDL_Point p) const
{
	if (!isActive())
		return false;
	return p.x >= _absolute_rect.x && p.x <= _absolute_rect.x + _absolute_rect.w && p.y >= _absolute_rect.y && p.y <= _absolute_rect.y + _absolute_rect.h;
}

void Button::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force || isDirty());
		if (d)
		{
			//LOGINFO << "rendering dirty button" << this << endl;
			if (hover())
				SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
			else
				_color.setRenderDrawColor(r);

			//SDL_RenderDrawRect(r, &_rect);
			//SDL_RenderFillRect(r, NULL);
		}
		Label::internalRender(r, d);
	}
}
Button* Button::clone() const
{
	Button* b = new Button(_relative_rect.w, _relative_rect.h);

	b->setActive(isActive());
	b->setHover(hover());
	b->setBackground(_regular_bg);
	b->setHoverBackground(_hover_bg);
	b->setText(getText());
	b->setTextAlignment(getTextAlignment());
	b->setTextSize(getTextSize());
	b->setTextColor(getTextColor());
	b->setColor(getColor());
	b->setPosition(_relative_rect.x, _relative_rect.y);
	b->Clickable::setCallback(Clickable::getCallback());

	return b;
}