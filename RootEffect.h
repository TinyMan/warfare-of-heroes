#pragma once
#include "OverTimeEffect.h"
class RootEffect :
	public OverTimeEffect
{
public:
	RootEffect(int duration = 0, Character* caster = nullptr);
	virtual ~RootEffect();

	virtual bool beginTurn();
	virtual RootEffect* clone() const {
		return new RootEffect(*this);
	}
};

