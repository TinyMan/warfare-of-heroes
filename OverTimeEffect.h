#pragma once
#include "Effect.h"
class OverTimeEffect :
	public Effect
{
public:
	OverTimeEffect(int duration = 0, string name = "Over Time Effect", Character* caster = nullptr);
	virtual ~OverTimeEffect();

	virtual void reset() { _duration = _max_duration; }
	bool isToDelete() const { return _to_delete; }

	virtual bool beginTurn() = 0;

	virtual bool apply(SpellTarget *target = nullptr);

	virtual void setTarget(SpellTarget* t) { _target = t; }

protected:
	SpellTarget* _target;
	int _duration;
	int _max_duration;
	bool _to_delete = false;

	bool newTurn();

};

