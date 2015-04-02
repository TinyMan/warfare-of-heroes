#pragma once
#include "AreaOfEffect.h"
class Cell;

class LineAoE :
	public AreaOfEffect
{
public:
	LineAoE(const Cell* first, const Cell* last);
	LineAoE(const Cell* first, const Cell* second, int range);

	virtual ~LineAoE();

	virtual void extrapole();
	virtual const Cell* getCell() const { return _first; }

protected:
	const Cell* _first;
	const Cell* _last;

};

