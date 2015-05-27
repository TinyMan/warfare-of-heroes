#include "ObstacleOctopus.h"
map<unsigned int, Texture> ObstacleOctopus::_obstacles_tex;

ObstacleOctopus::ObstacleOctopus(Cell* cell, GridOctopus* grid)
	: _grid(grid), _cell(cell)
{
	setZIndex(cell->getNumber());
}


ObstacleOctopus::~ObstacleOctopus()
{
}
void ObstacleOctopus::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force | isDirty());
		if (d && _cell && _grid)
		{
			drawObstacle(r, _cell->getNumber(), _cell->obstacle_type);
		}
	}
}
void ObstacleOctopus::drawObstacle(SDL_Renderer* r, unsigned int cell, unsigned int type)
{
	if (_obstacles_tex.count(type) != 1)
	{
		string texName = "obstacle_" + to_string(type);
		Texture tex = (*ServiceLocator::getTextureManager())[texName];
		_obstacles_tex[type] = Texture((int)_grid->getCellDimensions().x * 2, (int)_grid->getCellDimensions().y * 2, Color::TRANSPARENT, r);
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
	Point pos = _grid->getCellCenter(cell) - _grid->getCellDimensions()*1.5 / 2;
	pos.y -= _grid->getCellDimensions().y / 1.5;
	pos = toContainerCoordinates(_grid->toAbsoluteCoordinates(pos));
	SDL_Rect dst = { (int)pos.x, (int)pos.y, int(_grid->getCellDimensions().x*1.75), int(_grid->getCellDimensions().y*1.75) };
	_obstacles_tex[type].render(r, nullptr, &dst);
}
