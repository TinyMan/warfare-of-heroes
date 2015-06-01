#include "TargetSelector.h"
#include "Cell.h"

TargetSelector::TargetSelector()
{
}


TargetSelector::~TargetSelector()
{
}

SpellTarget* TargetSelector::getTargetFromCell(Cell* c) const
{
	SpellTarget* t = c->getObject();
	return !t ? c : t ;
}