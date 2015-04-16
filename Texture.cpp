#include "Texture.h"
#include <iostream>
#include "ServiceLocator.h"
using namespace std;
Texture::Texture(SDL_Texture* t)
	: _texture(t)
{
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
		SDL_Rect src = _defaultRect;
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