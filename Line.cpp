#include "Line.h"
#include "Geometry.h"


Line::Line(Point p1, Point p2)
	: _p1(p1), _p2(p2)
{
	calcEquation();
}
Line::Line(double x, double y, double x2, double y2)
	: _p1(x, y ), _p2( x2, y2 )
{
	calcEquation();
}


Line::~Line()
{
}

void Line::calcEquation()
{
	if (_p2.x != _p1.x)
		_slope = double(_p2.y - _p1.y) / (_p2.x - _p1.x);
	else
		_slope = 0;
	_c = _p1.y - _slope * _p1.x;
	// Y = _slope * x + _c
}
bool Line::hasIntersection(const Line& l) const
{
	return doIntersect(_p1, _p2, l._p1, l._p2);
}
Point Line::intersection(const Line& l) const
{
	Point* p = ::intersection(_p1, _p2, l._p1, l._p2);
	if (p)
		return *p;
	else
		return Point();
}
bool Line::intersection(const Line& l, Point* p) const
{
	Point * tmp = ::intersection(_p1, _p2, l._p1, l._p2);
	if (tmp)
	{
		*p = *tmp;
		return true;
	}
	return false;
}
int Line::intersectX(const Line& l) const
{
	Point p = intersection(l);
	return int(p.x);
}
int Line::intersectY(const Line& l) const
{
	Point p = intersection(l);
	return int(p.y);
}
ostream& operator<<(ostream& o, const Line& l)
{
	o << "Line: " << l._p1 << ", " << l._p2 << endl;
	o << "Equation: Y = " << l._slope << "X " << ((l._c < 0) ? ' ' : '+') << l._c << endl;
	return o;
}