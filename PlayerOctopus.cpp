#include "PlayerOctopus.h"
#include "ServiceLocator.h"

Texture PlayerOctopus::_basic_player;

PlayerOctopus::PlayerOctopus()
	: OctopusBaby(50,60)
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

}
void PlayerOctopus::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force || isDirty());
		if (d)
		{
			SDL_Rect dst;
			dst.x = 0; dst.y = 0;
			double ratiox = (double)_relative_rect.w /_basic_player.getWidth();
			double ratioy = (double)_relative_rect.h / _basic_player.getHeight();
			double ratio = min(ratioy, ratiox);

			dst.w = _basic_player.getWidth() * ratio;
			dst.h = _basic_player.getHeight() * ratio;

			SDL_RenderCopy(r, _basic_player, nullptr, &dst);
		}
	}
}