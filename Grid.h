#pragma once
#include <cstdlib>
#include <iostream>
#include <array>
#include "Cell.h"
#include "GameObject.h"
#include "SpellTarget.h"
#include "PathFinder.h"

using namespace std;


class Grid : public GameObject
{
public:
	enum DIRECTION
	{
		TOP,
		BOTTOM,
		RIGHT,
		LEFT,
		UNKNOWN
	};
	Grid();
	virtual ~Grid();

	void generateObstacle();
	/* TODO:: */
	/*virtual void update() {}
	virtual void initialize() {}*/

	void display(ostream& o=cout) const;
	void setObject(SpellTarget* go, int i, int j);
	void setObject(SpellTarget* go, unsigned int n);

	Cell* getCellAt(int i, int j);
	Cell* getCell(unsigned int n);
	list<Cell*> getAdjacentCells(Cell* c);

	// TODO: return the cell distance between cells at index i,j and x,y
	int getCellDistance(int i, int j, int x, int y);
	int getCellDistance(unsigned int n, unsigned int n2);

	// TODO: return the cell distance between cells
	static int getCellDistance(const Cell&, const Cell&);
	Cell* getCellFromCellAndDir(const Cell&, DIRECTION d, int pathLength);
	DIRECTION getDir(const Cell& c1, const Cell& c2);

	static const int WIDTH = 14;
	static const int HEIGHT = 14;
	static const unsigned int CELLS_NUMBER = (WIDTH * 2 - 1) * HEIGHT - WIDTH + 1;

	static unsigned int toCellNumber(int x, int y) { return (CELLS_NUMBER-1)/2 + x * WIDTH + y * (HEIGHT - 1); }

	virtual void beginTurn();

	static bool validCoordinates(int i, int j)
	{
		return i > (-WIDTH) && i <(WIDTH) && j >(-HEIGHT) && j < HEIGHT;
	}
	PathFinder<Cell*> pathFinder;

	vector<Cell*> getObstacles() const { return _obstacles; }
	static const int nbObstacles = 10;
private:
	map<unsigned int, Cell> _cells;
	map<int, map<int, unsigned int>> _cells_coordinates;
	vector<Cell*>  _obstacles;
};


