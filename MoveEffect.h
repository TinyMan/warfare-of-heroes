#pragma once
#include "Effect.h"

class Cell;

class MoveEffect :
	public Effect
{
public:
	
	MoveEffect(Cell* dest = nullptr, Character * caster = nullptr);

	virtual ~MoveEffect();

	virtual bool apply(SpellTarget* target);

	virtual void setCell(Cell* cell) { _cell = cell; }

protected:
	Cell * _cell;
};

