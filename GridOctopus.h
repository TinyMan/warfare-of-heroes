#pragma once
#include "OctopusBaby.h"
#include "Polygon.h"
#include "Grid.h"
#include "Hoverable.h"

class GridOctopus
	: public OctopusBaby
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

	virtual void update() override{};
	virtual bool isDirty() override { return _dirty; }
	virtual void setDirty(bool d = true) override { _dirty = d; }

protected:
	virtual void internalRender(SDL_Renderer* r, bool force = false) override{};

private:
	bool _dirty = true;
	Grid* _grid;
	unsigned int _width;
	unsigned int _height;
	Polygon _cellPolygon;

	Point _cellDimensions;

};