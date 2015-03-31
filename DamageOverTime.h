#pragma once
#include <string>
#include "SpellTarget.h"

using namespace std;

class DamageOverTime
{
public:
	DamageOverTime(int dmg = 0, int duration = 0, string name = "Unknown DoT", SpellTarget * t = nullptr);
	virtual ~DamageOverTime();

	virtual void beginTurn();

	bool isToDelete() const { return _to_delete; }
	void setTarget(SpellTarget * t) { _target = t; }

	friend ostream& operator<<(ostream& o, const DamageOverTime& dot);
protected:
	SpellTarget* _target;
	int _damage;
	int _duration;
	string _name;
	bool _to_delete = false;
};

