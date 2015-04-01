#pragma once
#include "Effect.h"

class Cell;

class MoveEffect :
	public Effect
{
public:
	
	MoveEffect(Cell* dest, Character * caster = nullptr);

	virtual ~MoveEffect();

	virtual bool apply(SpellTarget* target);

protected:
	Cell * _cell;
};

