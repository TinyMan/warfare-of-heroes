#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <list>
#include "Color.h"
#include "Line.h"

using namespace std;

class Polygon
{
public:
	Polygon();
	virtual ~Polygon();

	void addPoint(SDL_Point p);
	
	void draw(SDL_Renderer* r, Color c);
	void drawFill(SDL_Renderer* r, Color c);
	bool enclosesPoint(SDL_Point p) const;

	int size() const { return _points.size(); }
	vector<Line> getLines() const;
	
	Polygon operator+(const SDL_Point);
	friend ostream& operator<<(ostream&, const Polygon& p);
private:
	vector<SDL_Point> _points;
};