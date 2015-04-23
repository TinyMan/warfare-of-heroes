#pragma once
#include <SDL2/SDL.h>

class Color
{
public:
	Color(Uint8 r = 0, Uint8 g = 0, Uint8 b = 0, Uint8 a = 255);
	virtual ~Color();

	Uint8 r() const { return _r; }
	Uint8 g() const { return _g; }
	Uint8 b() const { return _b; }
	Uint8 a() const { return _a; }

	static const Color BLACK;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color TRANSPARENT;
private:
	Uint8 _r = 0;
	Uint8 _g = 0;
	Uint8 _b = 0;
	Uint8 _a = 255;

};

