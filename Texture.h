#pragma once
#include <SDL2/SDL.h>
#include <map>
#include <iostream>
#include "Geometry.h"
#include "Color.h"
using namespace std;

#define MAXWIDTH 1200
#define MAXHEIGHT 900
class Alignment
{
public:
	static const Uint8 UNKNOWN = 15;
	static const Uint8 CENTERX = 1;
	static const Uint8 CENTERY = 2;
	static const Uint8 LEFT = 4;
	static const Uint8 RIGHT = 0;
	static const Uint8 TOP = 8;
	static const Uint8 BOTTOM = 0;

};
/*
A Texture is a smart ptr to SDL_Texture
You should not use ptr to Texture
You should not use SDL_Texture*
SDL_Texture are automatically destroyed when there is no more ref to them
\TODO: add clone method to copy SDL_Structure
*/
class Texture
{
public:
	enum STYLE
	{
		STRETCH,
		FILL,
		FIT,
		TILE,
		CENTER
	};
	Texture(SDL_Texture* texture = nullptr);
	Texture(int w, int h, Color c = Color::TRANSPARENT, SDL_Renderer* r = nullptr, Uint32 f = SDL_PIXELFORMAT_UNKNOWN, int a = SDL_TEXTUREACCESS_TARGET);
	Texture(const Texture&);
	Texture& operator=(const Texture&);
	Texture& operator=( SDL_Texture*);

	operator SDL_Texture* () const { return _texture; }

	virtual ~Texture();

	void setTexture(SDL_Texture* t);
	SDL_Texture* getTexture() const { return _texture; }
	int getWidth() const { return _w; }
	int getHeight() const { return _h; }
	Uint32 getFormat() const { return _format; }
	int getAccess() const { return _access; }

	void render(SDL_Renderer* r, SDL_Rect* srcrect = nullptr, SDL_Rect* dstrect = nullptr, STYLE s = STRETCH);
	void render(SDL_Renderer* r, STYLE s, SDL_Rect* srcrect = nullptr, SDL_Rect* dstrect = nullptr) { render(r, srcrect, dstrect, s); }
	static void combineRect(SDL_Rect& dst, SDL_Rect& src, STYLE style = CENTER);
	bool valid() const { return _texture != nullptr; }
	void fill(SDL_Renderer* r, Color c);

	void setRenderTarget();
	void resetRenderTarget();
protected:
	void updateInfo();

private:
	SDL_Texture* _texture = nullptr;
	SDL_Texture* _old_renderTarget = nullptr;
	SDL_Renderer* _renderer = nullptr;
	int _w;
	int _h;
	int _access;
	Uint32 _format;
	SDL_Rect _defaultRect;
	bool _destroyTexture = false;
	string _name;
	static void addRef(SDL_Texture*);
	static void delRef(SDL_Texture*);
	static map<SDL_Texture*, Uint32> _garbages;
};
