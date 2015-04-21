#include "Button.h"
#include "EventCallback.h"
#include "Game.h"

Button::Button(SDL_Rect rect) : OctopusBaby(rect)
{
	_color = { 255, 0, 0, 0 };
}
Button::Button(int x, int y, int w, int h) : OctopusBaby( x, y, w, h )
{
	_color = { 255, 0, 0, 0 };
}


Button::~Button()
{
}


bool Button::isInArea(SDL_Point p) const
{
	if (!isActive())
		return false;
	return p.x >= _rect.x && p.x <= _rect.x + _rect.w && p.y >= _rect.y && p.y <= _rect.y + _rect.h;
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
				SDL_SetRenderDrawColor(r, 0, 0, 255, 0);
			else
				SDL_SetRenderDrawColor(r, _color.r, _color.g, _color.b, _color.a);

			//SDL_RenderDrawRect(r, &_rect);
			SDL_RenderFillRect(r, NULL);
		}
	}
	
}