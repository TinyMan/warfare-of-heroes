#include "OctopusBaby.h"
#include "Game.h"

OctopusBaby::OctopusBaby()
{
	_rect = { 0, 0, GAMEINST->getOctopus()->getWWidth(), GAMEINST->getOctopus()->getWHeight() };
	initialize();
}
OctopusBaby::OctopusBaby(SDL_Rect r)
	: _rect(r)
{
	initialize();
}
OctopusBaby::OctopusBaby(int x, int y, int w, int h)
	: _rect({ x, y, w, h })
{
	initialize();
}
OctopusBaby::~OctopusBaby()
{
}

void OctopusBaby::initialize()
{
	LOGINFO << "Initializing new OctopusBaby" << endl;
	_texture = SDL_CreateTexture(GAMEINST->getOctopus()->getRenderer(), SDL_GetWindowPixelFormat(GAMEINST->getOctopus()->getWindow()), SDL_TEXTUREACCESS_TARGET, _rect.w, _rect.h);
	if (!_texture.valid())
		LOGERR << "Could not initialize Octopus Baby (failed to create texture)" << endl;
	SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);
}
void OctopusBaby::setZIndex(int z)
{
	if (z != _z_index)
	{		
		_z_index = z;
		setSorted(false);
	}
}
bool OctopusBaby::operator<(const OctopusBaby& o) const
{
	return isAbove(o);
}
bool OctopusBaby::compare(const Sortable* s) const
{
	return isAbove(*(const OctopusBaby*)s);
}

void OctopusBaby::render(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		/* if dirty we need to redraw to _texture */
		bool dirty = isDirty();
		bool d = (force || dirty);
		if (dirty)
		{
			SDL_Texture * old = SDL_GetRenderTarget(r);
			if (SDL_SetRenderTarget(r, _texture) != 0)
			{
				LOGERR << "Error setting render target: " << SDL_GetError() << endl;
			}
			if (_background.valid())
				_background.render(r, Texture::STRETCH);
			else
			{
				SDL_SetRenderDrawColor(r, 0, 0, 0, 0);
				SDL_RenderClear(r);
			}
			internalRender(r, d);
			setDirty(false);
			SDL_SetRenderTarget(r, old);
		}
		if (d)
		{
			//LOGINFO << "Rendering Octopus Baby" << endl;
			if (SDL_RenderCopy(r, _texture, NULL, &_rect) != 0)
			{
				LOGERR << "Error renderCopy: " << SDL_GetError() << endl;
			}
		}
	}
	else
		setDirty(false);
}
