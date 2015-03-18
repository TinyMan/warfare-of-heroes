#pragma once
#include <cstdlib>
#include "Cell.h"
#include "DeadObject.h"

const int WIDTH = 14;
const int LENGTH = 30;

class Grid : public DeadObject
{
private :
	Cell arrayOfCells[WIDTH][LENGTH];
public:
	Grid();
	~Grid();

	void generateObstacle();

	void update() {}
	void initialize() {}
};


