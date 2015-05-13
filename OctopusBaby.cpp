#include "OctopusBaby.h"
#include "Game.h"
#include "Octopus.h"
#include "SpellRecap.h"

OctopusBaby::OctopusBaby()
{
	_relative_rect = { 0, 0, GAMEINST->getOctopus()->getWWidth(), GAMEINST->getOctopus()->getWHeight() };
	initialize();
}
OctopusBaby::OctopusBaby(int w, int h)
	: _relative_rect({ 0, 0, w, h })
{
	initialize();
}
OctopusBaby::OctopusBaby(SDL_Rect r)
	: _relative_rect(r)
{
	initialize();
}
OctopusBaby::OctopusBaby(int x, int y, int w, int h)
	: _relative_rect({ x, y, w, h })
{
	initialize();
}
OctopusBaby::~OctopusBaby()
{
}

void OctopusBaby::initialize()
{
	_absolute_rect = _relative_rect;
	_container_rect = { 0, 0, GAMEINST->getOctopus()->getWWidth(), GAMEINST->getOctopus()->getWHeight() };
	//LOGINFO << "Initializing new OctopusBaby" << endl;
	_texture = SDL_CreateTexture(GAMEINST->getOctopus()->getRenderer(), SDL_GetWindowPixelFormat(GAMEINST->getOctopus()->getWindow()), SDL_TEXTUREACCESS_TARGET, _relative_rect.w, _relative_rect.h);
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
			//LOGINFO << "octopusbaby is dirty" << endl;
			_texture.setRenderTarget();

			if (_background.valid())
				_background.render(r, Texture::STRETCH);
			else
			{
				_background_color.clearRenderer(r);
			}
			internalRender(r, d);
			setDirty(false);
			
			_texture.resetRenderTarget();
		}
		if (d)
		{
			//LOGINFO << "Rendering octopusbaby" << endl;
			if (SDL_RenderCopy(r, _texture, NULL, &_relative_rect) != 0)
			{
				LOGERR << "Error renderCopy: " << SDL_GetError() << endl;
			}
		}
	}
	else
	{
		//setDirty(false);
	}
}
void OctopusBaby::updateAbsoluteRect()
{
	_absolute_rect.x = _relative_rect.x + _container_rect.x;
	_absolute_rect.y = _relative_rect.y + _container_rect.y;
	_absolute_rect.w = min(_relative_rect.w, _container_rect.w - _relative_rect.x);
	_absolute_rect.h = min(_relative_rect.h, _container_rect.h - _relative_rect.y);
	setDirty();
}
void OctopusBaby::setPosition(int x, int y)
{
	_relative_rect.x = x;
	_relative_rect.y = y;
	updateAbsoluteRect();
}
void OctopusBaby::setPosition(Uint8 al)
{
	if (al & Alignment::CENTERX)
		_relative_rect.x = (_container_rect.w / 2) - (_relative_rect.w / 2);
	else if (!(al & Alignment::LEFT))
		_relative_rect.x = (_container_rect.w) - _relative_rect.w;
	if (al & Alignment::CENTERY)
		_relative_rect.y = (_container_rect.h / 2) - (_relative_rect.h / 2);
	else if (!(al & Alignment::TOP))
		_relative_rect.y = _container_rect.h - _relative_rect.h;

	updateAbsoluteRect();
}
void OctopusBaby::setPositionX(int x)
{
	_relative_rect.x = x;
	updateAbsoluteRect();
}
void OctopusBaby::setPositionY(int y)
{
	_relative_rect.y = y;
	updateAbsoluteRect();
}
void OctopusBaby::setAlpha(Uint8 alpha)
{
	Uint8 a;
	SDL_GetTextureAlphaMod(_texture, &a);
	if (a != alpha)
	{
		SDL_SetTextureAlphaMod(_texture, alpha);
		setDirty();
	}
}
Uint8 OctopusBaby::getAlpha() const
{
	Uint8 alpha;
	SDL_GetTextureAlphaMod(_texture, &alpha);
	return alpha;
}
bool OctopusBaby::isInArea(SDL_Point p) const
{
	if (!isActive())
		return false;
	return p.x >= _absolute_rect.x && p.x <= _absolute_rect.x + _absolute_rect.w && p.y >= _absolute_rect.y && p.y <= _absolute_rect.y + _absolute_rect.h;
}

Point OctopusBaby::toLocalCoordinates(const Point& p) const
{
	return p - Point(_absolute_rect.x, _absolute_rect.y);
}