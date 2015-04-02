#include "AreaOfEffect.h"


AreaOfEffect::AreaOfEffect(string name)
	: _name(name)
{
}


AreaOfEffect::~AreaOfEffect()
{
}

void AreaOfEffect::addCell(Cell* c)
{
	_cells.push_back(c);
}
