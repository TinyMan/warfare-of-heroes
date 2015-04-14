#include "Button.h"
#include "EventCallback.h"
#include "Game.h"

Button::Button(SDL_Rect rect) : _rect(rect)
{

}
Button::Button(int x, int y, int w, int h) : _rect({ x, y, w, h })
{

}


Button::~Button()
{
}

void Button::render(SDL_Renderer* r)
{
	internalRender(r);
}
bool Button::isInArea(SDL_Point p) const
{
	return p.x >= _rect.x && p.x <= _rect.x + _rect.w && p.y >= _rect.y && p.y <= _rect.y + _rect.h;
}

void Button::internalRender(SDL_Renderer* r)
{
	if (isDirty())
	{
		LOGINFO << "rendering dirty button" << endl;
		if (hover())
			SDL_SetRenderDrawColor(r, 0, 0, 255, 0);
		else
			SDL_SetRenderDrawColor(r, 255, 0, 0, 0);

		SDL_RenderDrawRect(r, &_rect);
		setDirty(false);
	}
}