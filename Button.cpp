#include "Button.h"
#include "EventCallback.h"
#include "Game.h"

Button::Button(SDL_Rect rect) : _rect(rect)
{
	_color = { 255, 0, 0, 0 };
}
Button::Button(int x, int y, int w, int h) : _rect({ x, y, w, h })
{
	_color = { 255, 0, 0, 0 };
}


Button::~Button()
{
}

void Button::render(SDL_Renderer* r, bool dirty)
{
	bool d = dirty || isDirty();
	if (d)
	{
		//LOGINFO << "rendering dirty button" << this << endl;
		if (hover())
			SDL_SetRenderDrawColor(r, 0, 0, 255, 0);
		else
			SDL_SetRenderDrawColor(r, _color.r, _color.g, _color.b, _color.a);

		//SDL_RenderDrawRect(r, &_rect);
		SDL_RenderFillRect(r, &_rect);
		setDirty(false);
	}
}
bool Button::isInArea(SDL_Point p) const
{
	return p.x >= _rect.x && p.x <= _rect.x + _rect.w && p.y >= _rect.y && p.y <= _rect.y + _rect.h;
}
