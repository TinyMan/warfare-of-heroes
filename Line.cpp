#include "Line.h"
#include "Geometry.h"


Line::Line(SDL_Point p1, SDL_Point p2)
	: _p1(p1), _p2(p2)
{
	calcEquation();
}
Line::Line(int x, int y, int x2, int y2)
	: _p1({ x, y }), _p2({ x2, y2 })
{
	calcEquation();
}


Line::~Line()
{
}

void Line::calcEquation()
{
	_slope = float(_p2.y - _p1.y) / (_p2.x - _p1.x);
	_c = _p1.y - _slope * _p1.x;
	// Y = _slope * x + _c
}
bool Line::hasIntersection(const Line& l) const
{
	return doIntersect(_p1, _p2, l._p1, l._p2);
}
SDL_Point Line::intersection(const Line& l) const
{
	SDL_Point ret = { 0, 0 };
	if (_slope != l._slope)
	{
		ret.x = int((l._c - _c) / (_slope - l._slope));
		ret.y = int(_slope * ret.x + _c);
	}
	return ret;
}
int Line::intersectX(const Line& l) const
{
	if (_slope != l._slope)
	{
		return int((l._c - _c) / (_slope - l._slope));
	}
	return 0;
}
int Line::intersectY(const Line& l) const
{
	SDL_Point p = intersection(l);
	return p.y;
}
ostream& operator<<(ostream& o, const Line& l)
{
	o << "Line: " << l._p1 << ", " << l._p2 << endl;
	o << "Equation: Y = " << l._slope << "X " << ((l._c < 0) ? ' ' : '+') << l._c << endl;
	return o;
}