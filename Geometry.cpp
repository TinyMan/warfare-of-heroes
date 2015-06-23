#include "Geometry.h"

// thanks to http://stackoverflow.com/questions/26076656/calculating-angle-between-two-points-java
double getAngleFromPoint(Point firstPoint, Point secondPoint) {

	if ((secondPoint.x > firstPoint.x)) {//above 0 to 180 degrees

		return (atan2((secondPoint.x - firstPoint.x), (firstPoint.y - secondPoint.y)) * 180 / M_PI);

	}
	else if ((secondPoint.x < firstPoint.x)) {//above 180 degrees to 360/0

		return 360 - (atan2((firstPoint.x - secondPoint.x), (firstPoint.y - secondPoint.y)) * 180 / M_PI);

	}//End if((secondPoint.x > firstPoint.x) && (secondPoint.y <= firstPoint.y))

	return atan2(0, 0);

}//End public float getAngleFromPoint(Point firstPoint, Point secondPoint)

SDL_Point operator+(const SDL_Point p1, const SDL_Point p2)
{
	return{ p1.x + p2.x, p1.y + p2.y };
}
bool operator==(const SDL_Point p1, const SDL_Point p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}
Point Point::operator-(const Point& p2) const
{
	return Point(x - p2.x, y - p2.y);
}
Point Point::operator*(double c) const
{
	return Point(x * c, y*c);
}
bool Point::operator <= (const Point& p) const
{
	Point p1 = abs(*this);
	Point p2 = abs(p);
	return p1.x <= p2.x && p1.y <= p2.y;
}
Point Point::operator+(const Point& p1) const
{
	return Point(p1.x + x, p1.y + y);
}
bool Point::operator!=(const Point& p) const
{
	return !(*this == p);
}
bool Point::operator==(const Point& p) const
{
	return (p.x == x) && (p.y == y);
}
Point Point::operator/(int n) const
{
	return Point(x / n, y / n);
}
Point abs(const Point& p)
{
	return Point(abs(p.x), abs(p.y));
}
ostream& operator<<(ostream& o, const SDL_Point& p)
{
	o << "(" << p.x << ", " << p.y << ")";
	return o;
}
ostream& operator<<(ostream& o, const Point& p)
{
	o << (SDL_Point)p;
	return o;
}
ostream& operator<<(ostream& o, const SDL_Rect& r)
{
	o << "{ " << r.x << ", " << r.y << ", " << r.w << ", " << r.h << " }";
	return o;
}

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool onSegment(Point p, Point q, Point r)
{
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
		q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
		return true;

	return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
	// See 10th slides from following link for derivation of the formula
	// http://www.dcs.gla.ac.uk/~pat/52233/slides/Geometry1x1.pdf
	double val = (q.y - p.y) * (r.x - q.x) -
		(q.x - p.x) * (r.y - q.y);

	if (int(val) == 0) return 0;  // colinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}
// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
	// Find the four orientations needed for general and
	// special cases
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// p1, q1 and p2 are colinear and p2 lies on segment p1q1
	if (o1 == 0 && onSegment(p1, p2, q1)) return true;

	// p1, q1 and p2 are colinear and q2 lies on segment p1q1
	if (o2 == 0 && onSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are colinear and p1 lies on segment p2q2
	if (o3 == 0 && onSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are colinear and q1 lies on segment p2q2
	if (o4 == 0 && onSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases
}

Point* intersection(Point p1, Point p2, Point p3, Point p4) {
	// Store the values for fast access and easy
	// equations-to-code conversion
	double x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
	double y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

	double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	// If d is zero, there is no intersection
	if (d == 0) return NULL;

	// Get the x and y
	double pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	double x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	double y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

	// Check if the x and y coordinates are within both lines
	if (x < min(x1, x2) || x > max(x1, x2) ||
		x < min(x3, x4) || x > max(x3, x4)) return NULL;
	if (y < min(y1, y2) || y > max(y1, y2) ||
		y < min(y3, y4) || y > max(y3, y4)) return NULL;

	// Return the point of intersection
	Point* ret = new Point();
	ret->x = x;
	ret->y = y;
	return ret;
}
bool operator==( const SDL_Rect& r1,  const SDL_Rect& r2)
{
	return (r1.x == r2.x) && (r1.y == r2.y) && (r1.w == r2.w) && (r1.h == r2.h);
}