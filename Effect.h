#pragma once
#include <string>

using namespace std;
class SpellTarget;

class Effect
{
public:
	Effect(string name = "Unknown effect", SpellTarget* target = nullptr);
	virtual ~Effect();

	virtual bool apply(SpellTarget* target) = 0;

	friend ostream& operator<<(ostream& o, const Effect& e);
protected:
	SpellTarget* _target;
	string _name;

};

