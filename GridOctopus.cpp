#include "GridOctopus.h"
#include "Game.h"
#include "Octopus.h"

GridOctopus::GridOctopus(Grid* grid, unsigned int width, unsigned int height)
	: OctopusBaby(width, height), _grid(grid), _width(width), _height(height)
{
	// calculate the width and height of a cell
	_cellDimensions.x = (double)_width / Grid::WIDTH;
	_cellDimensions.y = (double)_height / Grid::HEIGHT;


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
}
GridOctopus::~GridOctopus()
{

}
Cell* GridOctopus::getCellFromPoint(const Point & p) const
{
	// TODO not complete
	int x = (p.x / _cellDimensions.x + p.y / _cellDimensions.y) / 2;
	int y = (p.y / _cellDimensions.y - p.x / _cellDimensions.x) / 2;

	return _grid->getCellAt(x, y);
}