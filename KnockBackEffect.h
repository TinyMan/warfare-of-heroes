#pragma once
#include "MoveEffect.h"
class KnockBackEffect :
	public MoveEffect
{
public:
	KnockBackEffect(int nbCells = 0, Character* caster = nullptr);
	virtual ~KnockBackEffect();

	virtual bool apply(SpellTarget* target);
protected:
	int _nbCells;
};

