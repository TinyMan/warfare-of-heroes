#include "KnockBackEffect.h"
#include "Grid.h"
#include "Game.h"


KnockBackEffect::KnockBackEffect(int nbCells, Character* caster)
	: MoveEffect(nullptr, caster), _nbCells(nbCells)
{
}


KnockBackEffect::~KnockBackEffect()
{
}

bool KnockBackEffect::apply(SpellTarget* target)
{
	if (target)
	{
		Grid::DIRECTION d = GAMEINST->getGrid()->getDir(*_caster->getCell(), *target->getCell());
		if (d != Grid::UNKNOWN)
		{
			setCell(GAMEINST->getGrid()->getCellFromCellAndDir(*target->getCell(), d, _nbCells));
			return MoveEffect::apply(target);
		}
	}
	return false;
}
