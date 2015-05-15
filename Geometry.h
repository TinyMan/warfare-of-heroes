#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <algorithm>
#define INF 10000
using namespace std;

class Point
{
public:
	double x;
	double y;
	Point(double x = 0, double y = 0) : x(x), y(y){}
	Point(SDL_Point p) : x(p.x), y(p.y) {}
	operator SDL_Point() const { return{ int(x), int(y) }; }
	Point operator-(const Point&) const;
	Point operator*(const double) const;
	bool operator!=(const Point&) const;
	bool operator==(const Point&) const;
	Point& operator/(int n) const;
};

SDL_Point operator+(const SDL_Point p1, const SDL_Point p2);
ostream& operator<<(ostream& o, const SDL_Point& p);
ostream& operator<<(ostream& o, const Point& p);
ostream& operator<<(ostream& o, const SDL_Rect& r);

bool onSegment(Point p, Point q, Point r);
int orientation(Point p, Point q, Point r);
bool doIntersect(Point p1, Point q1, Point p2, Point q2); 
inline double Dot(const Point& a, const Point& b){ return (a.x*b.x) + (a.y*b.y); }
inline double PerpDot(const Point& a, const Point& b){ return (a.y*b.x) - (a.x*b.y); }

Point* intersection(Point p1, Point p2, Point p3, Point p4);

bool operator==(const SDL_Rect&, const SDL_Rect&);