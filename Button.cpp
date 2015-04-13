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
	SDL_SetRenderDrawColor(r, 255, 0, 0, 0);
	SDL_RenderDrawRect(r, &_rect);
}
bool Button::isInArea(SDL_Point p) const
{
	return p.x >= _rect.x && p.x <= _rect.x + _rect.h && p.y >= _rect.y && p.y <= _rect.y + _rect.h;
}