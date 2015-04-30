#pragma once
#include "OctopusBaby.h"
#include "Hoverable.h"
#include "Cell.h"
#include "Polygon.h"

class CellOctopus :
	public OctopusBaby, public Hoverable
{
public:
	CellOctopus(Cell* c);
	virtual ~CellOctopus();

	virtual void update() {}

	virtual void setDirty(bool d = true) { _dirty = d; }
	virtual bool isDirty() { return _dirty; }
	virtual bool isInArea(SDL_Point p) const;

	virtual void onMouseIn(MouseEvents::MotionEvent* e);
	virtual void onMouseOut(MouseEvents::MotionEvent* e);
	virtual void updateAbsoluteRect();

protected:
	virtual void internalRender(SDL_Renderer* r, bool force = false);

private:
	bool _dirty = true;

	Cell* _cell = nullptr;
	Polygon _absolute_polygon;

	static Texture _regular_cell;
	static Texture _hover_cell;
	static void drawCell(SDL_Renderer* r, Texture& t, Color c = Color(255, 255, 255, 255));
	static Polygon polygon;
	static const SDL_Point p1;
	static const SDL_Point p2;
	static const SDL_Point p3;
	static const SDL_Point p4;
};

