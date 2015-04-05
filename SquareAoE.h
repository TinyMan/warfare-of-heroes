#pragma once
#include "AreaOfEffect.h"
class SquareAoE :
	public AreaOfEffect
{
public:
	SquareAoE(const Cell* center = nullptr, int len = 0);

	virtual ~SquareAoE();

	void setCenter(Cell* c);
	void setLen(int len);

	virtual void extrapole();

	/* getters */
	virtual void displayBasic(ostream& o) const;
	virtual const Cell* getCell() const { return _center; }

protected:
	const Cell* _center;
	int _len;
};

