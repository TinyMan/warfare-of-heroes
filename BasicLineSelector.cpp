#include "BasicLineSelector.h"
#include "LineAoE.h"

BasicLineSelector::BasicLineSelector(int r, std::function<const Cell*(Cell* second, Grid::DIRECTION* dir)> f)
	: range(r), getFirstCell(f)
{
}


BasicLineSelector::~BasicLineSelector()
{
}

SpellTarget* BasicLineSelector::getTargetFromCell(Cell* c) const
{
	try{
		Grid::DIRECTION dir;
		return new LineAoE(getFirstCell(c, &dir), dir, range);
	}
	catch (...)
	{
		return c;
	}
}
