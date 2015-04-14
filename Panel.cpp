#include "Panel.h"
#include "Game.h"

Panel::Panel(SDL_Renderer* r,SDL_Rect rect)
	: _rect(rect)
{
	initialize(r);
}
Panel::Panel(SDL_Renderer* r, int x, int y, int w, int h)
	: _rect({x, y, w, h})
{
	initialize(r);
}

void Panel::initialize(SDL_Renderer* r)
{
	LOGINFO << "Initialising new Panel" << endl;
	LOGINFO << _rect.w << " " << _rect.h << endl;
	_texture = SDL_CreateTexture(r, SDL_GetWindowPixelFormat(GAMEINST->getOctopus()->getWindow()), SDL_TEXTUREACCESS_TARGET, _rect.w, _rect.h);
}

Panel::~Panel()
{
	SDL_DestroyTexture(_texture);
}

void Panel::render(SDL_Renderer* r)
{
	internalRender(r);
	SDL_RenderCopy(r, _texture, NULL, &_rect);	
}

void Panel::internalRender(SDL_Renderer* r)
{
	/* if dirty we need to redraw to _texture */
	if (isDirty())
	{
		LOGINFO << this << " is dirty, need render" << endl;
		SDL_SetRenderTarget(r, _texture);
		/* draw the contained octopus babies onto the texture */
		for (auto e : _list)
		{
			//LOGINFO << "Rendering a baby in the panel " << endl;
			e->render(r);
		}
		SDL_SetRenderTarget(r, NULL);
		/* the texture is now up to date */
		setDirty(false);
	}
}
void Panel::triggerModifyEvent()
{
	//LOGINFO << "Triggerin modify event " << this << endl;
	(new ModifyEvent(reinterpret_cast<Modifiable*>(this)))->dispatch();
}