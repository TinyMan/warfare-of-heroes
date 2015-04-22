#pragma once
#include <SDL2/SDL.h>
#include <iostream>
using namespace std;
#define MAXWIDTH 1200
#define MAXHEIGHT 900

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
	//Texture(const Texture&);

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
protected:
	void updateInfo();

private:
	SDL_Texture* _texture = nullptr;
	int _w;
	int _h;
	int _access;
	Uint32 _format;
	SDL_Rect _defaultRect;
};

ostream& operator<<(ostream& o, const SDL_Rect&);