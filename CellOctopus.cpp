#include "CellOctopus.h"
#include "Game.h"
#include "Octopus.h"

Texture CellOctopus::_regular_cell;
Texture CellOctopus::_hover_cell;
const SDL_Point CellOctopus::p1 = { 0, 25 };
const SDL_Point CellOctopus::p2 = { 25, 0 };
const SDL_Point CellOctopus::p3 = { 50, 25 };
const SDL_Point CellOctopus::p4 = { 25, 50 };

CellOctopus::CellOctopus()
	: OctopusBaby(50, 25)
{
	if (!_regular_cell.valid())
	{
		SDL_Renderer * r = GAMEINST->getOctopus()->getRenderer();

		_regular_cell = Texture(50, 50);
		drawCell(r, _regular_cell);
	}
	if (!_hover_cell.valid())
	{
		SDL_Renderer * r = GAMEINST->getOctopus()->getRenderer();
		_hover_cell = Texture(50, 50);
		drawCell(r, _hover_cell, Color::BLUE);
	}
	setBackground(_regular_cell);
}


CellOctopus::~CellOctopus()
{
}

void CellOctopus::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = force | isDirty();
		if (d)
		{
			
		}
	}
}
void CellOctopus::drawCell(SDL_Renderer* r, Texture& t, Color c)
{
	t.setRenderTarget();
	SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
	SDL_RenderClear(r);
	SDL_SetRenderDrawColor(r, c.r(), c.g(), c.b(), c.a());
	SDL_RenderDrawLine(r, p1.x, p1.y, p2.x, p2.y);
	SDL_RenderDrawLine(r, p2.x, p2.y, p3.x, p3.y);
	SDL_RenderDrawLine(r, p3.x, p3.y, p4.x, p4.y);
	SDL_RenderDrawLine(r, p4.x, p4.y, p1.x, p1.y);
	t.resetRenderTarget();
}
void CellOctopus::onMouseIn(MouseEvents::MotionEvent* e)
{
	Hoverable::onMouseIn(e);
	setBackground(_hover_cell);
}
void CellOctopus::onMouseOut(MouseEvents::MotionEvent* e)
{
	Hoverable::onMouseOut(e);
	setBackground(_regular_cell);
}
bool CellOctopus::isInArea(SDL_Point p) const
{
	// TODO: real check (check if p is in polygon p1,p2,p3,p4)
	if (!isActive())
		return false;
	return OctopusBaby::isInArea(p);
}