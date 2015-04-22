#include "Texture.h"
#include <iostream>
#include "ServiceLocator.h"
#include "Game.h"
using namespace std;
Texture::Texture(SDL_Texture* t)
	: _texture(t)
{
	updateInfo();
}
Texture::Texture(int w, int h, SDL_Renderer* r, Uint32 f, int a)
{
	if (f == SDL_PIXELFORMAT_UNKNOWN)
		f = SDL_GetWindowPixelFormat(GAMEINST->getOctopus()->getWindow());
	if (!r)
		r = GAMEINST->getOctopus()->getRenderer();
	_texture = SDL_CreateTexture(r, f, a, w, h);
	updateInfo();
}

Texture::~Texture()
{
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
			dstrect = new SDL_Rect({ 0, 0, MAXWIDTH, MAXHEIGHT });
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

ostream& operator<<(ostream& o, const SDL_Rect& r)
{
	o << "{ " << r.x << ", " << r.y << ", " << r.w << ", " << r.h << " }";
	return o;
}
void FillTexture(SDL_Renderer* r, Texture& t, Color c)
{
	SDL_Texture* old = SDL_GetRenderTarget(r);

	SDL_SetRenderTarget(r, t);
	SDL_SetRenderDrawColor(r, c.r(), c.g(), c.b(), c.a());
	SDL_RenderFillRect(r, NULL);

	SDL_SetRenderTarget(r, old);
}