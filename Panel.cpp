#include "Panel.h"
#include "Game.h"
#include "ServiceLocator.h"

Panel::Panel(SDL_Rect rect)
	: _rect(rect)
{
	initialize();
}
Panel::Panel(int x, int y, int w, int h)
	: _rect({ x, y, w, h })
{
	initialize();
}

void Panel::initialize()
{
	/*LOGINFO << "Initialising new Panel" << endl;
	LOGINFO << _rect.w << " " << _rect.h << endl;*/
	_texture = SDL_CreateTexture(GAMEINST->getOctopus()->getRenderer(), SDL_GetWindowPixelFormat(GAMEINST->getOctopus()->getWindow()), SDL_TEXTUREACCESS_TARGET, _rect.w, _rect.h);
}

Panel::~Panel()
{
	SDL_DestroyTexture(_texture);
}

void Panel::render(SDL_Renderer* r, bool dirty)
{
	/* if dirty we need to redraw to _texture */
	bool d = (dirty || isDirty()) && isActive();
	if (d)
	{
		//LOGINFO << this << " is dirty, need render" << endl;
		SDL_SetRenderTarget(r, _texture);
		/* draw the contained octopus babies onto the texture */
		for (auto e : _list)
		{
			//LOGINFO << "Rendering a baby in the panel " << endl;
			e->render(r, d);
		}
		SDL_SetRenderTarget(r, NULL);
		/* the texture is now up to date */
		setDirty(false);
	}
	SDL_RenderCopy(r, _texture, NULL, &_rect);
}

void Panel::update()
{
	MyList::update();
	
}