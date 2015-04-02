#pragma once
#include <string>

using namespace std;
class SpellTarget;
class Character;

class Effect
{
public:
	Effect(string name = "Unknown effect", Character* caster = nullptr);
	virtual ~Effect();

	virtual bool apply(SpellTarget* target) = 0;

	friend ostream& operator<<(ostream& o, const Effect& e);
protected:
	Character* _caster;
	string _name;

};

