#include "PlayerOctopus.h"
#include "ServiceLocator.h"

Texture PlayerOctopus::_basic_player;

PlayerOctopus::PlayerOctopus(Character* c, GridOctopus* grid)
	: OctopusBaby(PLAYER_WIDTH, PLAYER_HEIGHT), _character(c), _grid(grid)
{
	if (!_basic_player.valid())
	{
		_basic_player = (*ServiceLocator::getTextureManager())["player_basic"];
	}
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
			//LOGINFO << "updating player octopus" << endl;

			// update position based on cell
			const Cell* c = _character->getCell();
			//LOGINFO << "player is on cell " << *c << endl;

			if (c)
			{
				SDL_Rect cellRect = _grid->getCellOctopus(c)->getRelativeRect();
				//LOGINFO << "rect is " << cellRect << endl;

				SDL_Point midDown = { cellRect.x + cellRect.w / 2, cellRect.y + cellRect.h };

				double ratiox = (double)_relative_rect.w / _basic_player.getWidth();
				double ratioy = (double)_relative_rect.h / _basic_player.getHeight();
				double ratio = min(ratioy, ratiox);
				setPosition(midDown.x - _basic_player.getWidth() * ratio / 2, midDown.y - _basic_player.getHeight() * ratio);
			
				//LOGINFO << "new position: " << getPosition() << endl;
			}

		}
		//setActive(false);
	}
}
void PlayerOctopus::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force || isDirty());
		if (d)
		{
			SDL_Rect dst = _relative_rect;
			double ratiox = (double)_relative_rect.w /_basic_player.getWidth();
			double ratioy = (double)_relative_rect.h / _basic_player.getHeight();
			double ratio = min(ratioy, ratiox);

			dst.w = _basic_player.getWidth() * ratio;
			dst.h = _basic_player.getHeight() * ratio;

			SDL_RenderCopy(r, _basic_player, nullptr, &dst);
		}
	}
}