#include "GridOctopus.h"
#include "Game.h"
#include "Octopus.h"

GridOctopus::GridOctopus(Grid* grid, unsigned int width, unsigned int height)
	: OctopusBaby(width, height), _grid(grid), _width(width), _height(height)
{
	// calculate the width and height of a cell
	_cellDimensions.x = (double)_width / Grid::WIDTH;
	_cellDimensions.y = (double)_height / Grid::HEIGHT;


	_cellPolygon.addPoint({ 0, _cellDimensions.y / 2 });
	_cellPolygon.addPoint({ _cellDimensions.x/2, 0});
	_cellPolygon.addPoint({ _cellDimensions.x, _cellDimensions.y / 2 });
	_cellPolygon.addPoint({ _cellDimensions.x/2, _cellDimensions.y });


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

			Polygon poly = _cellPolygon + pos;

			_cellsPolygon.emplace(n, poly);
			n++;
		}
	}

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
		found = it->second.enclosesPoint(point);
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
	if (hover())
	{
		//TODO change (this is just to debug)
		setDirty();
	}
}
void GridOctopus::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force | isDirty());
		if (d)
		{
			SDL_Point p;
			SDL_GetMouseState(&p.x, &p.y);
			Cell* higlighted_cell = getCellFromPoint(p);

			if (higlighted_cell)
			{
				_cellsPolygon[higlighted_cell->getNumber()].drawFill(r, Color::BLUE);
			}
		}
	}
}