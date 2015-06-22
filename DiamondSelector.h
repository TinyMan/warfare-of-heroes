#pragma once
#include "TargetSelector.h"
class DiamondSelector :
	public TargetSelector
{
public:
	DiamondSelector(unsigned int radius);
	virtual ~DiamondSelector();

	virtual SpellTarget* getTargetFromCell(Cell* c) const override;
	unsigned int radius;
};

