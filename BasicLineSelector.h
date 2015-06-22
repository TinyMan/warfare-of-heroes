#pragma once
#include <functional>
#include "TargetSelector.h"
#include "Grid.h"

class BasicLineSelector :
	public TargetSelector
{
public:
	BasicLineSelector(int range, std::function<const Cell*(Cell* second, Grid::DIRECTION* dir)> getFirstCell);
	virtual ~BasicLineSelector();

	virtual SpellTarget* getTargetFromCell(Cell* second) const override;

	int range;
	function<const Cell*(Cell* second, Grid::DIRECTION* dir)> getFirstCell;
};

