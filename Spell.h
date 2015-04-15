#pragma once
#include <string>
#include <list>
#include "Character.h"
#include "Cell.h"
#include "SpellTarget.h"
#include "DamageOverTime.h"

using namespace std;

/* declaration */
class Spell
{
public:
	Spell(string name = "Unknown Spell", Character* caster = nullptr, int cd = 0, int cp_cost = 0, int mp_cost = 0, int hp_cost = 0, int min_scope = 0, int max_scope = 0, bool is_inline = false);
	virtual ~Spell();

	virtual bool cast(SpellTarget* target = nullptr);
	virtual void beginTurn();

	virtual bool canCastOn(SpellTarget* target);

	/* setters */
	void setCDMax(int cd) { _max_cooldown = cd; }
	void setCPCost(int cost) { _cp_cost = cost; }
	void setMPCost(int cost) { _mp_cost = cost; }
	void setHPCost(int cost) { _hp_cost = cost; }
	void setMinScope(int min_scope) { _min_scope = min_scope; }
	void setMaxScope(int max_scope) { _max_scope = max_scope; }
	void setInline(bool il) { _is_inline = il; }
	void addEffect(Effect* effect);

	/* getters */
	int getMaxScope() const { return _max_scope; }

	friend ostream& operator<<(ostream& o, const Spell& s);
protected:	
	int _min_scope;
	int _max_scope;
	int _cp_cost;
	int _hp_cost;
	int _mp_cost;
	bool _is_inline;
	string _name;

	list<Effect*> _effects;
	Character* _caster;
private:
	int _max_cooldown;
	int _cooldown = 0;

};
