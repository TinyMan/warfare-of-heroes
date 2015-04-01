#include "MoveEffect.h"
#include "SpellTarget.h"

MoveEffect::MoveEffect(Cell * dst, Character* caster)
	: Effect("Move effect", caster), _cell(dst)
{
}


MoveEffect::~MoveEffect()
{
}

bool MoveEffect::apply(SpellTarget* st)
{
	if (st)
	{		
		return st->move(*_cell, false);
	}
	return false;
}