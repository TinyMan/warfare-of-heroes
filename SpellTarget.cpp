#include "SpellTarget.h"
#include "Grid.h"
#include "Effect.h"

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

bool SpellTarget::hasEffect(string name) const
{
	bool found = false;
	for (auto& e : getEffects())
	{
		found = name == e->getName() && !e->isToDelete();
		if (found)
			break;
	}
	return found;
}