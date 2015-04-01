#pragma once
#include <string>
#include "SpellTarget.h"
using namespace std;

class Effect
{
public:
	Effect(string name = "Unknown effect", SpellTarget* target = nullptr);
	virtual ~Effect();

	virtual bool apply(SpellTarget* target) = 0;

protected:
	SpellTarget* _target;
	string _name;

};

