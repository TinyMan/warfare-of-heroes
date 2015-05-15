#include "GridOctopus.h"
#include "Game.h"
#include "Octopus.h"

GridOctopus::GridOctopus(Grid* grid, unsigned int width, unsigned int height)
	: OctopusBaby(width, height), _grid(grid), _width(width), _height(height)
{
	// calculate the width and height of a cell
	_cellDimensions.x = (double)_width / Grid::WIDTH;
	_cellDimensions.y = (double)_height / Grid::HEIGHT;

	Polygon p1, p2, p3, p4; // triangles
	p1.addPoint(Point(0, _cellDimensions.y / 2));
	p1.addPoint(Point(_cellDimensions.x / 2, 0));
	p1.addPoint(Point(_cellDimensions.x / 2, _cellDimensions.y / 2));
	p2.addPoint(Point(_cellDimensions.x / 2, 0));
	p2.addPoint(Point(_cellDimensions.x, _cellDimensions.y / 2));
	p2.addPoint(Point(_cellDimensions.x / 2, _cellDimensions.y / 2));
	p3.addPoint(Point(_cellDimensions.x, _cellDimensions.y / 2));
	p3.addPoint(Point(_cellDimensions.x / 2, _cellDimensions.y / 2));
	p3.addPoint(Point(_cellDimensions.x / 2, _cellDimensions.y));
	p4.addPoint(Point(0, _cellDimensions.y / 2));
	p4.addPoint(Point(_cellDimensions.x / 2, _cellDimensions.y / 2));
	p4.addPoint(Point(_cellDimensions.x / 2, _cellDimensions.y));

	_cellPolygons.push_back(p1);
	_cellPolygons.push_back(p2);
	_cellPolygons.push_back(p3);
	_cellPolygons.push_back(p4);

	// draw the grid
	/* code from leekwars
	for (var i = 0; i < this.tilesX; i++) {

		ctx.beginPath();
		ctx.moveTo(this.tileSizeX / 2 + i * this.tileSizeX, 0);
		ctx.lineTo(0, this.tileSizeY / 2 + i * this.tileSizeY);
		ctx.stroke();

		ctx.beginPath();
		ctx.moveTo(this.tileSizeX / 2 + i * this.tileSizeX, this.gridHeight);
		ctx.lineTo(0, this.gridHeight - this.tileSizeY / 2 - i * this.tileSizeY);
		ctx.stroke();

		ctx.beginPath();
		ctx.moveTo(this.gridWidth - this.tileSizeX / 2 - i * this.tileSizeX, 0);
		ctx.lineTo(this.gridWidth, this.tileSizeY / 2 + i * this.tileSizeY);
		ctx.stroke();

		ctx.beginPath();
		ctx.moveTo(this.gridWidth - this.tileSizeX / 2 - i * this.tileSizeX, this.gridHeight);
		ctx.lineTo(this.gridWidth, this.gridHeight - this.tileSizeY / 2 - i * this.tileSizeY);
		ctx.stroke();
	}
	*/
	SDL_Renderer* r = GAMEINST->getOctopus()->getRenderer();

	Texture bg(_width, _height);
	bg.setRenderTarget();
	Color::BLACK.setRenderDrawColor(r);
	int x1, x2, y1, y2;
	for (int i = 0; i < Grid::WIDTH; i++)
	{
		x1 = int(_cellDimensions.x / 2 + i * _cellDimensions.x);
		y1 = 0;
		x2 = 0;
		y2 = int(_cellDimensions.y / 2 + i * _cellDimensions.y);
		SDL_RenderDrawLine(r, x1, y1, x2, y2);
		

		x1 = int(_cellDimensions.x / 2 + i * _cellDimensions.x);
		y1 = _height;
		x2 = 0;
		y2 = int(_height - _cellDimensions.y / 2 - i * _cellDimensions.y);
		SDL_RenderDrawLine(r, x1, y1, x2, y2);

		x1 = int(_width - _cellDimensions.x / 2 - i * _cellDimensions.x);
		y1 = 0;
		x2 = _width;
		y2 = int(_cellDimensions.y / 2 + i * _cellDimensions.y);
		SDL_RenderDrawLine(r, x1, y1, x2, y2);

		x1 = int(_width - _cellDimensions.x / 2 - i * _cellDimensions.x);
		y1 = _height;
		x2 = _width;
		y2 = int(_height - _cellDimensions.y / 2 - i * _cellDimensions.y);
		SDL_RenderDrawLine(r, x1, y1, x2, y2);


	}
	bg.resetRenderTarget();
	setBackground(bg);

	unsigned int n = 0;
	for (int j = 0; j < Grid::HEIGHT * 2 - 1; ++j)
	{
		bool big = j % 2 == 0;
		int width = big ? Grid::WIDTH : Grid::WIDTH - 1;

		for (int i = 0; i < width; i++)
		{
			Point pos;
			pos.x = i * _cellDimensions.x + (!big * _cellDimensions.x / 2);
			pos.y = j * _cellDimensions.y/2;

			vector<Polygon> poly = _cellPolygons;
			for (auto& e : poly)
			{
				e = e + pos;
			}
			_cellsPolygon.emplace(n, poly);
			n++;
		}
	}

	setEveryMovesNotification(true);
}

GridOctopus::~GridOctopus()
{

}
Cell* GridOctopus::getCellFromPoint(const Point & p) const
{
	Point point = toLocalCoordinates(p);
	auto& it = _cellsPolygon.begin();
	bool found = false;
	do
	{
		for (auto& e : it->second)
		{
			found = e.enclosesPoint(point);
			if (found)
				break;
		}		
	} while (!found && ++it != _cellsPolygon.end());

	if (found)
	{
		return _grid->getCell(it->first);
	}
	else
		return nullptr;
}

void GridOctopus::update()
{
}
void GridOctopus::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force | isDirty());
		if (d)
		{
			if (_higlighted_cell)
			{
				for (auto& e : _cellsPolygon[_higlighted_cell->getNumber()])
				{
					e.drawFill(r, Color::BLUE);
				}
			}			
		}
	}
}

void GridOctopus::onMouseMove(MouseEvents::MotionEvent* e)
{
	Hoverable::onMouseMove(e);
	Cell* c = getCellFromPoint(e->getPos());
	if (_higlighted_cell != c)
	{
		_higlighted_cell = c;
	}
	else
	{
		setDirty(false);
	}
}
void GridOctopus::onMouseOut(MouseEvents::MotionEvent* e)
{
	Hoverable::onMouseOut(e);
	_higlighted_cell = nullptr;
}
Point GridOctopus::getCellCenter(const Cell* cell) const
{ 
	if (!cell)
		throw string("Cell cannot be null");
	unsigned int n = cell->getNumber();
	if (_cellsPolygon.count(n) != 1)
		throw string("Unknown cell");

	Polygon poly = _cellsPolygon.at(n)[0];

	vector<Point> points = poly.getPoints();

	return points[2];
}