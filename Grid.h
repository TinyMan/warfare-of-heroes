#pragma once
#include <cstdlib>
#include <iostream>
#include "Cell.h"
#include "DeadObject.h"

using namespace std;


class Grid : public DeadObject
{
public:
	Grid();
	virtual ~Grid();

	void generateObstacle();
	/* TODO:: */
	/*virtual void update() {}
	virtual void initialize() {}*/

	void display(ostream& o=cout) const;
	void setObject(GameObject* go, int i, int j);

	Cell* getCellAt(int i, int j);

	// TODO: return the cell distance between cells at index i,j and x,y
	int getCellDistance(int i, int j, int x, int y);
	// TODO: return the cell distance between cells
	int getCellDistance(const Cell&, const Cell&);

	static const int WIDTH = 14;
	static const int HEIGHT = 30;

private:
	Cell arrayOfCells[WIDTH][HEIGHT];
};


