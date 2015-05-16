#pragma once
#include <unordered_map>
#include "OctopusBaby.h"
#include "Polygon.h"
#include "Grid.h"
#include "Hoverable.h"
#include "Clickable.h"
#include "GridEvents.h"

using namespace Events::GridEvents;

class GridOctopus
	: public OctopusBaby, public Hoverable, public Clickable
{
public:
	/* represent the grid grid, in a container of size width x height 
		cells are autosized
		you should use height = width/2
	*/
	GridOctopus(Grid* grid, unsigned int width, unsigned int height);
	~GridOctopus();

	unsigned int getWidth() const { return _width; }
	unsigned int getHeight() const { return _height; }

	Cell* getCellFromPoint(const Point& p) const;
	Point getCellCenter(const Cell* cell) const;
	Point getCellCenter(unsigned int cell) const;

	virtual void update() override;
	virtual bool isDirty() override { return _dirty; }
	virtual void setDirty(bool d = true) override { _dirty = d; }

	virtual bool isInArea(SDL_Point p) const
	{
		if (!isActive())
			return false;
		return p.x >= _absolute_rect.x && p.x <= _absolute_rect.x + _absolute_rect.w && p.y >= _absolute_rect.y && p.y <= _absolute_rect.y + _absolute_rect.h;
	}
	virtual void onMouseMove(MouseEvents::MotionEvent* e);
	virtual void onMouseOut(MouseEvents::MotionEvent* e);
	virtual void onClick(ClickEvent* e);

	void mark(vector<unsigned int> cells, Color color = Color::BLUE);
	void mark(unsigned int cell, Color color = Color::BLUE);
	void unmark(unsigned int cell);
	void unmark(vector<unsigned int> cells);
	void unmarkAll();

	const Cell* _higlighted_cell = nullptr;
protected:
	virtual void internalRender(SDL_Renderer* r, bool force = false) override;
	virtual void drawCell(SDL_Renderer* r, unsigned int cell, Color c);

private:
	bool _dirty = true;
	Grid* _grid;
	unsigned int _width;
	unsigned int _height;
	Polygon _cellDrawPolygon;
	vector<Polygon> _cellHitBox;
	map<unsigned int, Polygon> _cellsDrawPolygons;
	map<unsigned int, vector<Polygon>> _cellsHitboxes;
	map<unsigned int, Color> _markedCells;
	map<Color, Texture> _coloredCells;

	Point _cellDimensions;

};