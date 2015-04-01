#pragma once
#include "Effect.h"
class OverTimeEffect :
	public Effect
{
public:
	OverTimeEffect(int duration = 0, string name = "Over Time Effect", SpellTarget* t = nullptr);
	virtual ~OverTimeEffect();

	virtual void reset() { _duration = _max_duration; }
	bool isToDelete() const { return _to_delete; }

	virtual bool beginTurn();

	virtual bool apply(SpellTarget *target = nullptr);
protected:
	int _duration;
	int _max_duration;
	bool _to_delete = false;

};

