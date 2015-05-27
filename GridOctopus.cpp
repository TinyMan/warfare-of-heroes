#include "GridOctopus.h"
#include "Game.h"
#include "Octopus.h"

GridOctopus::GridOctopus(Grid* grid, unsigned int width, unsigned int height)
	: OctopusBaby(width, height), _grid(grid), _width(width), _height(height)
{
	// calculate the width and height of a cell
	_cellDimensions.x = (double)_width / Grid::WIDTH;
	_cellDimensions.y = (double)_height / Grid::HEIGHT;

	const double PAD = 0.5;
	Polygon p1, p2, p3, p4; // triangles
	p1.addPoint(Point(0, _cellDimensions.y / 2));
	p1.addPoint(Point(_cellDimensions.x / 2, 0));
	p1.addPoint(Point(_cellDimensions.x / 2, _cellDimensions.y / 2));
	p2.addPoint(Point(_cellDimensions.x / 2, 0));
	p2.addPoint(Point(_cellDimensions.x + PAD, _cellDimensions.y / 2));
	p2.addPoint(Point(_cellDimensions.x / 2, _cellDimensions.y / 2));
	p3.addPoint(Point(_cellDimensions.x, _cellDimensions.y / 2));
	p3.addPoint(Point(_cellDimensions.x / 2, _cellDimensions.y / 2));
	p3.addPoint(Point(_cellDimensions.x / 2, _cellDimensions.y + PAD));
	p4.addPoint(Point(0, _cellDimensions.y / 2));
	p4.addPoint(Point(_cellDimensions.x / 2, _cellDimensions.y / 2));
	p4.addPoint(Point(_cellDimensions.x / 2, _cellDimensions.y));

	_cellHitBox.push_back(p1);
	_cellHitBox.push_back(p2);
	_cellHitBox.push_back(p3);
	_cellHitBox.push_back(p4);

	_cellDrawPolygon.addPoint(_cellHitBox[0].getPoints()[0]);
	_cellDrawPolygon.addPoint(_cellHitBox[0].getPoints()[1]);
	_cellDrawPolygon.addPoint(_cellHitBox[1].getPoints()[1]);
	_cellDrawPolygon.addPoint(_cellHitBox[2].getPoints()[2]);

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
			pos.x = (i * _cellDimensions.x + (!big * _cellDimensions.x / 2+0.9));
			pos.y = (j * _cellDimensions.y/2);

			vector<Polygon> poly = _cellHitBox;
			for (auto& e : poly)
			{
				e = e + pos;
			}
			_cellsHitboxes.emplace(n, poly); 
			_cellsDrawPolygons.emplace(n, _cellDrawPolygon + pos);
			_cellsDrawPolygons[n][0].x = floor(_cellsDrawPolygons[n][0].x - 0.1);
			_cellsDrawPolygons[n].convertInt();
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

	/*
	Optimization:
	Since p could be at the bottom or the right of the grid, we don't need to iterate through the whole grid (it takes time)
	We can calculate how many lines thereare between 0 and p.y (lets say j)
	Then we need to find the cell number of the j-th line
	Same for column
	*/
	unsigned int n_lines = max(int((point.y) / _cellDimensions.y)-1, 0);
	unsigned int n_columns = max(int((point.x) / _cellDimensions.x), 0);
	unsigned int n = n_lines * (Grid::WIDTH * 2 - 1) + n_columns;

	auto& it = _cellsHitboxes.find(n);
	bool found = false;
	do
	{
		for (auto& e : it->second)
		{
			found = e.enclosesPoint(point);
			if (found)
				break;
		}		
	} while (!found && ++it != _cellsHitboxes.end());

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

			for (auto& p : _markedCells)
			{
				drawCell(r, p.first, p.second);
			}
			/*for (auto& o : _grid->getObstacles())
			{
				drawObstacle(r, o->getNumber(), o->obstacle_type);
			}*/
		}
	}
}

void GridOctopus::drawCell(SDL_Renderer* r, unsigned int cell, Color color)
{
	if (_coloredCells.count(color) != 1)
	{
		_coloredCells[color] = Texture((int)_cellDimensions.x, (int)_cellDimensions.y, Color::TRANSPARENT, r);
		_coloredCells[color].setRenderTarget();
		_cellsDrawPolygons[0].drawFill(r, color);
		_coloredCells[color].resetRenderTarget();
		SDL_SetTextureBlendMode(_coloredCells[color], SDL_BLENDMODE_BLEND);
	}
	Point pos = getCellCenter(cell) - _cellDimensions / 2;
	SDL_Rect dst = { (int)pos.x, (int)pos.y, (int)_cellDimensions.x, (int)_cellDimensions.y };
	_coloredCells[color].render(r,nullptr, &dst);
}
void GridOctopus::drawObstacle(SDL_Renderer* r, unsigned int cell, unsigned int type)
{
	if (_obstacles_tex.count(type) != 1)
	{
		string texName = "obstacle_" + to_string(type);
		Texture tex =	(*ServiceLocator::getTextureManager())[texName];
		_obstacles_tex[type] = Texture((int)_cellDimensions.x * 2, (int)_cellDimensions.y*2, Color::TRANSPARENT, r);
		_obstacles_tex[type].setRenderTarget();
		tex.render(r, Texture::FIT);
		if (type == Cell::Tree)
		{
			SDL_Rect dst = { 0, 0, _obstacles_tex[type].getWidth() / 2, _obstacles_tex[type].getHeight() };
			tex.render(r, Texture::FIT, nullptr, &dst);
		}
		_obstacles_tex[type].resetRenderTarget();
		SDL_SetTextureBlendMode(_obstacles_tex[type], SDL_BLENDMODE_BLEND);
	}
	Point pos = getCellCenter(cell) - _cellDimensions*1.5 / 2;
	pos.y -= _cellDimensions.y / 1.5;
	SDL_Rect dst = { (int)pos.x, (int)pos.y, int(_cellDimensions.x*1.75), int(_cellDimensions.y*1.75) };
	_obstacles_tex[type].render(r, nullptr, &dst);
}
void GridOctopus::onMouseMove(MouseEvents::MotionEvent* e)
{
	Hoverable::onMouseMove(e);
	setDirty(false);
	Cell* c = getCellFromPoint(e->getPos());
	if (c && _higlighted_cell != c)
	{
		_higlighted_cell = c;
		(new CellHover(c))->dispatch();
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

	return getCellCenter(cell->getNumber());
}
Point GridOctopus::getCellCenter(unsigned int n) const
{
	if (_cellsHitboxes.count(n) != 1)
		throw string("Unknown cell");

	Polygon poly = _cellsHitboxes.at(n)[0];

	vector<Point> points = poly.getPoints();

	return points[2];
}
void GridOctopus::mark(vector<unsigned int> cells, Color color)
{
	for (unsigned int c : cells)
	{
		mark(c, color);
	}
}
void GridOctopus::mark(unsigned int cell, Color color)
{
	if (cell > Grid::CELLS_NUMBER)
		throw string("cell number not in range");
	OctopusBaby::setIfDifferent(_markedCells[cell], color);
	//setDirty();
}
void GridOctopus::unmark(unsigned int cell)
{
	if(_markedCells.erase(cell) ==1)
		setDirty();
}
void GridOctopus::unmarkAll()
{
	if (_markedCells.size() > 0)
	{
		_markedCells.clear();
		setDirty();
	}
}

void GridOctopus::unmark(vector<unsigned int> cells)
{
	for (unsigned int c : cells)
	{
		unmark(c);
	}
}
void GridOctopus::onClick(ClickEvent* e)
{
	Point pos = e->getPos();
	if (Cell* c = getCellFromPoint(pos))
	{
		unsigned int cell = c->getNumber();

		(new CellClick(e->button(), cell))->dispatch();
	}
}