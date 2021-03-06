#pragma once
#include <string>
#include "SpellTarget.h"
#include "OverTimeEffect.h"

using namespace std;

class DamageOverTime
	: public OverTimeEffect
{
public:
	DamageOverTime(int dmg = 0, int duration = 0, Character * caster = nullptr, string name = "Unknown DoT");
	virtual ~DamageOverTime();

	virtual bool beginTurn();
	virtual DamageOverTime* clone() const {
		return new DamageOverTime(*this);
	}

	bool isToDelete() const { return _to_delete; }
	void setTarget(SpellTarget * t) { _target = t; }

	friend ostream& operator<<(ostream& o, const DamageOverTime& dot);
protected:	
	int _damage;

};

