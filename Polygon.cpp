#include "Polygon.h"
#include "Geometry.h"


Polygon::Polygon()
{
}


Polygon::~Polygon()
{
}

void Polygon::addPoint(Point p)
{
	_points.push_back(p);
}

void Polygon::draw(SDL_Renderer* r, Color c)
{
	if (_points.size() > 2)
	{
		SDL_SetRenderDrawColor(r, c.r(), c.g(), c.b(), c.a());
		unsigned int i = _points.size()-1;
		SDL_RenderDrawLine(r, (int)_points[0].x, (int)_points[0].y, (int)_points[i].x, (int)_points[i].y);
		for (i = 1; i < _points.size(); i++)
		{
			SDL_RenderDrawLine(r, (int)_points[i - 1].x, (int)_points[i - 1].y, (int)_points[i].x, (int)_points[i].y);
		}
	}
}
void Polygon::drawFill(SDL_Renderer * r, Color c)
{
	if (_points.size() < 3)
		return;
	int w, h;
	SDL_GetRendererOutputSize(r, &w, &h);
	SDL_SetRenderDrawColor(r, c.r(), c.g(), c.b(), c.a());

	vector<Line> lines = getLines();
	list<int> intersectionX;
	// for each line
	for (int y = 0; y < h; y++)
	{
		// build the list of intersections between current scanline and each polygon line
		intersectionX.clear();
		Line l(0, y, w, y);
		Point tmp;
		for (Line polygon_line : lines)
		{
			if (polygon_line.intersection(l, &tmp))
				intersectionX.push_back((int)tmp.x);
		}

		// sort
		intersectionX.sort();

		// draw;
		vector<int> x(intersectionX.begin(), intersectionX.end());
		for (unsigned int i = 0; i < x.size(); i+=2)
		{
			SDL_RenderDrawLine(r, x[i], y, x[i+1], y);
		}
	}
}
// Source: http://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/
bool Polygon::enclosesPoint(const Point &p) const
{
	unsigned int n = _points.size();
	// There must be at least 3 vertices in polygon[]
	if (n < 3)  
		return false;

	// Create a point for line segment from p to infinite
	Point extreme = { INF, p.y };

	// Count intersections of the above line with sides of polygon
	int count = 0, i = 0;
	do
	{
		int next = (i + 1) % n;

		// Check if the line segment from 'p' to 'extreme' intersects
		// with the line segment from 'polygon[i]' to 'polygon[next]'
		if (doIntersect(_points[i], _points[next], p, extreme))
		{
			// If the point 'p' is colinear with line segment 'i-next',
			// then check if it lies on segment. If it lies, return true,
			// otherwise false
			if (orientation(_points[i], p, _points[next]) == 0)
				return onSegment(_points[i], p, _points[next]);

			count++;
		}
		i = next;
	} while (i != 0);

	// Return true if count is odd, false otherwise
	return count & 1;  // Same as (count%2 == 1)
}
vector<Line> Polygon::getLines() const
{
	vector<Line> ret;
	if (_points.size() > 2)
	{
		unsigned int i = _points.size() - 1;
		ret.emplace_back(_points[0].x, _points[0].y, _points[i].x, _points[i].y);
		for (i = 1; i < _points.size(); i++)
		{
			ret.emplace_back(_points[i - 1].x, _points[i - 1].y, _points[i].x, _points[i].y);
		}
	}
	return ret;
}
Polygon Polygon::operator+(const Point& p)
{
	Polygon po;
	for (auto e : _points)
	{
		po.addPoint(p + e);
	}
	return po;
}

ostream& operator<<(ostream& o, const Polygon& p)
{
	o << "Polygon: ";
	for (auto e : p._points)
	{
		o << e << endl;
	}
	return o;
}