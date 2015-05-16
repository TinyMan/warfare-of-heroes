#include "DiamondSelector.h"
#include "DiamondAoE.h"

DiamondSelector::DiamondSelector(unsigned int r)
	: radius(r)
{
}


DiamondSelector::~DiamondSelector()
{
}
SpellTarget* DiamondSelector::getTargetFromCell(Cell* c) const
{
	return new DiamondAoE(c, radius);
}
