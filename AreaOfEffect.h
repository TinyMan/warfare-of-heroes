#pragma once
#include <string>
#include <list>
#include "SpellTarget.h"
class Cell;

using namespace std;

class AreaOfEffect :
	public SpellTarget
{
public:
	AreaOfEffect(string name="Unknown AoE");
	virtual ~AreaOfEffect();

	list<Cell*> getCells() const { return _cells; }
	void addCell(Cell* c);

protected:
	string _name;
	list<Cell*> _cells;
};

