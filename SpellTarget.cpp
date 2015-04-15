#include "SpellTarget.h"
#include "Grid.h"

SpellTarget::SpellTarget()
{
}


SpellTarget::~SpellTarget()
{
}
int SpellTarget::getDistance(const SpellTarget& st) const
{
	return Grid::getCellDistance(*getCell(), *st.getCell());
}
