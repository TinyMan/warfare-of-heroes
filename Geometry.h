#include <SDL2/SDL.h>
#include <iostream>

#define max(a,b) (a < b ? b : a)
#define min(a,b) (a < b ? a : b)
#define INF 10000
using namespace std;

typedef SDL_Point Point;

SDL_Point operator+(const SDL_Point p1, const SDL_Point p2);
ostream& operator<<(ostream& o, const SDL_Point& p);
ostream& operator<<(ostream& o, const SDL_Rect& r);

bool onSegment(Point p, Point q, Point r);
int orientation(Point p, Point q, Point r);
bool doIntersect(Point p1, Point q1, Point p2, Point q2);