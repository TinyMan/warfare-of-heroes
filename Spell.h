#pragma once
#include <string>
#include "Character.h"
#include "Cell.h"
#include "SpellTarget.h"
#include "DamageOverTime.h"

using namespace std;

/* declaration */
class Spell
{
public:
	Spell(string name = "Unknown Spell", Character* caster = nullptr, int cd = 0, int dmg = 0, int heal = 0, int cost = 0, int min_scope = 0, int max_scope = 0, bool is_inline = false, DamageOverTime* dot=nullptr);
	virtual ~Spell();


	template<class Target>
	bool cast(Target* target = nullptr);
	virtual void beginTurn();

	template<class Target>
	bool canCastOn(Target* target);

	void setDamage(int dmg) { _damage = dmg; }
	void setCDMax(int cd) { _max_cooldown = cd; }
	void setHeal(int heal) { _heal = heal; }
	void setCost(int cost) { _cost = cost; }
	void setMinScope(int min_scope) { _min_scope = min_scope; }
	void setMaxScope(int max_scope) { _max_scope = max_scope; }
	void setInline(bool il) { _is_inline = il; }
	void setDot(DamageOverTime* dot) { _dot = dot; }

	friend ostream& operator<<(ostream& o, const Spell& s);
protected:
	
	int _damage;
	int _heal;
	int _min_scope;
	int _max_scope;
	int _cost;
	bool _is_inline;
	string _name;
	DamageOverTime *_dot;

	Character* _caster;
private:
	int _max_cooldown;
	int _cooldown = 0;

};

template<class Target>
bool Spell::cast(Target* target)
{
	if (canCastOn(target))
	{
		_cooldown = _max_cooldown;
		_caster->removeCapaciyPoint(_cost);
		target->lowerHitPoint(_damage);
		target->lowerHitPoint(-_heal);
		target->setDot(_dot);

		LOGINFO << _caster->getName() << " : Casting " << _name << " on ";
		target->displayBasic(LOGINFO);
		LOGINFO << endl;
		return true;

	}
	LOGWARN << _caster->getName() << " : Fail cast " << _name << endl;
	return false;
}
template<class Target>
bool Spell::canCastOn(Target* target)
{
	if (_caster)
	{
		int distance = _caster->getDistance(*target);
		if (distance <= _max_scope && distance >= _min_scope)
		{
			if (_caster->getCP() >= _cost)
				return true;
		}
	}
	return false;
}
