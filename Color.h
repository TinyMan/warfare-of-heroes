#pragma once
#include <SDL2/SDL.h>

class Color
{
public:
	Color(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255);
	virtual ~Color();

	void setRenderDrawColor(SDL_Renderer* r) const { SDL_SetRenderDrawColor(r, _r, _g, _b, _a); }
	void clearRenderer(SDL_Renderer * r) const { setRenderDrawColor(r); SDL_RenderClear(r); }

	Uint8 r() const { return _r; }
	Uint8 g() const { return _g; }
	Uint8 b() const { return _b; }
	Uint8 a() const { return _a; }

	operator Uint32 () const;

	static const Color BLACK;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color TRANSPARENT;
	static const Color WHITE;
	static const Color FONTCOLOR;
	static const Color BGCOLOR;
	bool operator==(const Color& c) const;
	bool operator!=(const Color& c) const;
	bool operator<(const Color& c) const;
private:
	Uint8 _r = 0;
	Uint8 _g = 0;
	Uint8 _b = 0;
	Uint8 _a = 255;

};

