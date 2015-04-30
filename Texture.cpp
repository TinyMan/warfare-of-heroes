#include "Texture.h"
#include <iostream>
#include "ServiceLocator.h"
#include "Game.h"
#include "Octopus.h"
map<SDL_Texture*, Uint32> Texture::_garbages;

Texture::Texture(SDL_Texture* t)
	: _texture(t)
{
	updateInfo();
	addRef(_texture);
}
Texture::Texture(int w, int h, Color c, SDL_Renderer* r, Uint32 f, int a)
{
	if (f == SDL_PIXELFORMAT_UNKNOWN)
		f = SDL_GetWindowPixelFormat(GAMEINST->getOctopus()->getWindow());
	if (!r)
		r = GAMEINST->getOctopus()->getRenderer();
	_renderer = r;
	_texture = SDL_CreateTexture(r, f, a, w, h);
	fill(r, c);
	updateInfo();
	addRef(_texture);
}
Texture::Texture(const Texture& t)
{
	_texture = t._texture;
	updateInfo();
	addRef(_texture);
}

Texture& Texture::operator=(const Texture& t)
{
	delRef(_texture);
	_texture = t._texture;
	updateInfo();
	addRef(_texture);
	
	return *this;
}
Texture& Texture::operator=(SDL_Texture* t)
{
	delRef(_texture);
	_texture = t;
	updateInfo();
	addRef(_texture);

	return *this;
}
Texture::~Texture()
{
	delRef(_texture);
}

void Texture::setTexture(SDL_Texture* t)
{
	_texture = t;
	updateInfo();
}

void Texture::updateInfo()
{
	SDL_QueryTexture(_texture, &_format, &_access, &_w, &_h);
	_defaultRect = { 0, 0, _w, _h };
}
void Texture::render(SDL_Renderer* r, SDL_Rect* srcrect, SDL_Rect* dstrect, STYLE s)
{
	if (r)
	{
		if (!dstrect)
		{
			int w, h; 
			SDL_GetRendererOutputSize( r, &w, &h);
			dstrect = new SDL_Rect({ 0, 0, w, h });
		}
		if (!srcrect)
			srcrect = new SDL_Rect(_defaultRect);
		SDL_Rect src = *srcrect;
		SDL_Rect dst = *dstrect;
		combineRect(src, dst, s);
		SDL_RenderCopy(r, _texture, &src, &dst);
	}
}

void Texture::combineRect(SDL_Rect& src, SDL_Rect& dst, STYLE style)
{
	// TODO : finish
	//LOGINFO << "Combining rects " << src << " and " << dst << endl;
	switch (style)
	{
	case Texture::STRETCH:
		break;
	case Texture::FILL:
		break;
	case Texture::FIT:
		break;
	case Texture::TILE:
		break;
	case Texture::CENTER:
		dst.x = (dst.w  - src.w) / 2;
		dst.y = (dst.h  - src.h) / 2;
		dst.w = src.w;
		dst.h = src.h;
		
		break;
	default:
		break;
	}
	//LOGINFO << "Combined rects " << src << " and " << dst << endl;

}

void Texture::fill(SDL_Renderer* r, Color c)
{
	if (_texture)
	{
		SDL_Texture* old = SDL_GetRenderTarget(r);

		SDL_SetRenderTarget(r, *this);
		SDL_SetRenderDrawColor(r, c.r(), c.g(), c.b(), c.a());
		SDL_RenderFillRect(r, NULL);

		SDL_SetRenderTarget(r, old);
	}
}
void Texture::setRenderTarget()
{
	if (!_renderer)
		_renderer = GAMEINST->getOctopus()->getRenderer();
	if (_renderer)
	{
		_old_renderTarget = SDL_GetRenderTarget(_renderer);
		if (SDL_SetRenderTarget(_renderer, _texture) != 0)
		{
			LOGERR << "Error setting render target: " << SDL_GetError() << endl;
		}
	}
}
void Texture::resetRenderTarget()
{
	if (!_renderer)
		_renderer = GAMEINST->getOctopus()->getRenderer();
	if (_renderer)
	{
		if (SDL_SetRenderTarget(_renderer, _old_renderTarget) != 0)
		{
			LOGERR << "Error setting render target: " << SDL_GetError() << endl;
		}
		_old_renderTarget = nullptr;
	}
}
void Texture::addRef(SDL_Texture* t)
{
	if (t)
	{
		if (_garbages.count(t) == 1)
		{
			_garbages[t]++;
			//LOGINFO << "SDL_Texture* " << t << " already registered: " << _garbages[t] << endl;
		}
		else
		{
			_garbages[t] = 1;
			//LOGINFO << "New SDL_Texture* " << t << endl;
		}
	}
}
void Texture::delRef(SDL_Texture* _texture)
{
	if (_texture)
	{
		if (!_garbages.empty() && _garbages.count(_texture) == 1)
		{
			Uint32 c = _garbages[_texture];
			if (c > 1)
			{
				_garbages[_texture] = c - 1;
				//LOGINFO << "Ref count for " << _texture << " is now " << c - 1 << endl;
			}
			else if (c == 1)
			{
				//LOGINFO << "Need to destroy SDL_Texture* " << _texture << "(" << "b" << ")" << endl;
				SDL_DestroyTexture(_texture);
				_garbages.erase(_texture);
			}
			else
			{
				//LOGERR << "PROBLEMMMMME" << endl;
				_garbages.erase(_texture);
			}
		}
		else
		{
			//LOGERR << "Error SDL_Texture* not count" << endl;
		}
	}
}