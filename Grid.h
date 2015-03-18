#pragma once
#include "Cell.h"

const int WIDTH = 14;
const int LENGTH = 30;

class Grid
{
private :
	Cell arrayOfCells[WIDTH][LENGTH];
public:
	Grid();
	~Grid();
};


