#pragma once
#include "SquareAoE.h"

class DiamondAoE :
	public SquareAoE
{
public:
	DiamondAoE(const Cell* center = nullptr, int len = 0);
	virtual ~DiamondAoE();

	virtual void extrapole();
};

