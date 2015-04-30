#pragma once
#include <SDL2/SDL.h>
#include <iostream>
using namespace std;
class Line
{
public:
	Line(SDL_Point p1 = { 0, 0 }, SDL_Point p2 = { 0, 0 });
	Line(int x, int y, int x2, int y2);
	virtual ~Line();

	bool hasIntersection(const Line& l) const;
	SDL_Point intersection(const Line& l) const;
	int intersectX(const Line& l) const;
	int intersectY(const Line& l) const;
	friend ostream& operator<<(ostream& o, const Line& l);
private:
	SDL_Point _p1;
	SDL_Point _p2;
	float _slope = 0;
	float _c = 0;

	void calcEquation();
};

