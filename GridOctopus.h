#pragma once
#include "Panel.h"
#include "Grid.h"
#include "CellOctopus.h"

class GridOctopus :
	public Panel
{
public:
	GridOctopus(Grid* g);
	virtual ~GridOctopus();

private:
	Grid* _grid = nullptr;
	CellOctopus* _cells[Grid::WIDTH][Grid::HEIGHT];
};

