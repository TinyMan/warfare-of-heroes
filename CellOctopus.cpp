#include "CellOctopus.h"
#include "Game.h"
#include "Octopus.h"

Texture CellOctopus::_regular_cell;
Texture CellOctopus::_hover_cell;
Polygon CellOctopus::polygon;
const SDL_Point CellOctopus::p1 = { 0, 12 };
const SDL_Point CellOctopus::p2 = { 25, 0 };
const SDL_Point CellOctopus::p3 = { 50, 12 };
const SDL_Point CellOctopus::p4 = { 25, 25 };

CellOctopus::CellOctopus(Cell* c)
	: OctopusBaby(50, 25), _cell(c)
{
	if (!_regular_cell.valid())
	{
		SDL_Renderer * r = GAMEINST->getOctopus()->getRenderer();

		_regular_cell = Texture(50, 25);
		drawCell(r, _regular_cell);
	}
	if (!_hover_cell.valid())
	{
		SDL_Renderer * r = GAMEINST->getOctopus()->getRenderer();
		_hover_cell = Texture(50, 25);
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
	if (polygon.size() == 0)
	{
		polygon.addPoint(p1);
		polygon.addPoint(p2);
		polygon.addPoint(p3);
		polygon.addPoint(p4);
	}
	t.setRenderTarget();
	SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
	SDL_RenderClear(r);

	polygon.draw(r, c);

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
	return _absolute_polygon.enclosesPoint(p);
}
void CellOctopus::updateAbsoluteRect()
{
	OctopusBaby::updateAbsoluteRect();
	_absolute_polygon = polygon + getAbsolutePosition();
}