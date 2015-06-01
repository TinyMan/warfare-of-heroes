#pragma once
#include "SpellTarget.h"

using namespace std;

class TargetSelector
{
public:
	TargetSelector();
	virtual ~TargetSelector();

	virtual SpellTarget* getTargetFromCell(Cell* c) const;

};

