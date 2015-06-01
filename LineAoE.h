#pragma once
#include "AreaOfEffect.h"
class Cell;

class LineAoE :
	public AreaOfEffect
{
public:
	LineAoE(const Cell* first, const Cell* last);
	LineAoE(const Cell* first, const Cell* second, int range);
	LineAoE(const Cell* first, Grid::DIRECTION direction, int range);

	virtual ~LineAoE();

	virtual void extrapole();
	virtual const Cell* getCell() const { return _last; }

	friend ostream& operator<<(ostream& o, const LineAoE& l);
protected:
	const Cell* _first;
	const Cell* _last;

};

