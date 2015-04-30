#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "Geometry.h"
using namespace std;
class Line
{
public:
	Line(Point p1 = { 0, 0 }, Point p2 = { 0, 0 });
	Line(double x, double y, double x2, double y2);
	virtual ~Line();

	bool hasIntersection(const Line& l) const;
	Point intersection(const Line& l) const;
	bool intersection(const Line& l, Point* p) const;
	int intersectX(const Line& l) const;
	int intersectY(const Line& l) const;
	friend ostream& operator<<(ostream& o, const Line& l);

	Point p1() const { return _p1; }
	Point p2() const { return _p2; }
private:
	Point _p1;
	Point _p2;
	double _slope = 0;
	double _c = 0;

	void calcEquation();
};

