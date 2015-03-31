#include "Spell.h"

/* definition */

Spell::Spell(string name, Character* caster, int cd, int dmg, int heal, int cost, int min_scope, int max_scope, bool is_inline)
	: _name(name), _caster(caster), _max_cooldown(cd), _damage(dmg), _heal(heal), _cost(cost), _min_scope(min_scope), _max_scope(max_scope), _is_inline(is_inline)
{
}


Spell::~Spell()
{
}

void Spell::beginTurn()
{
	if (_cooldown > 0)
		_cooldown--;
}
ostream& operator<<(ostream& o, const Spell& s)
{
	o << "Displaying spell: " << s._name << endl;
	o << "|-- Damage: " << s._damage << endl;
	/* ... */
	return o;
}


