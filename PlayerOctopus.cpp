#include "PlayerOctopus.h"
#include "ServiceLocator.h"

Texture PlayerOctopus::_basic_player;

PlayerOctopus::PlayerOctopus(Character* c, GridOctopus* grid)
	: OctopusBaby(PLAYER_WIDTH, PLAYER_HEIGHT), _character(c), _grid(grid)
{
	if (!_basic_player.valid())
	{
		_basic_player = (*ServiceLocator::getTextureManager())["knight"];
	}
	setBgColor(Color::TRANSPARENT);
}


PlayerOctopus::~PlayerOctopus()
{
}


void PlayerOctopus::update()
{
	if (isActive())
	{
		if (_character)
		{
			// update position based on cell
			const Cell* c = _character->getCell();

			if (c)
			{
				Point cellCenter = toContainerCoordinates(_grid->toAbsoluteCoordinates(_grid->getCellCenter(c)));
				
				double ratio = getRatio();

				SDL_Point pos = { int(cellCenter.x - _basic_player.getWidth() * ratio / 2), int(cellCenter.y - _basic_player.getHeight() * ratio + 7)};
				if ((Point)pos != getPosition())
				{
					setPosition(pos.x, pos.y);
				}
			}
		}
	}
}
void PlayerOctopus::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force || isDirty());
		if (d)
		{
			double ratio = getRatio();
			SDL_Rect dst = _relative_rect;
			dst.w = int(ratio * _basic_player.getWidth());
			dst.h = int(ratio * _basic_player.getHeight());
			dst.x = 0;
			dst.y = 0;
			_basic_player.render(r, nullptr, &dst);


		}
	}
}
double PlayerOctopus::getRatio() const
{
	double ratiox = (double)_relative_rect.w / _basic_player.getWidth();
	double ratioy = (double)_relative_rect.h / _basic_player.getHeight();
	return min(ratioy, ratiox);
}