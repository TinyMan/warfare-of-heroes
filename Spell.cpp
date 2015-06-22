#include "Spell.h"

/* definition */

Spell::Spell(string name, Character* caster, int cd,int cp_cost, int mp_cost, int hp_cost, int min_scope, int max_scope, bool is_inline)
	: _name(name), _caster(caster), _max_cooldown(cd), _cp_cost(cp_cost), _mp_cost(mp_cost), _hp_cost(hp_cost), _min_scope(min_scope), _max_scope(max_scope), _is_inline(is_inline), _selector(new TargetSelector())
{
}


Spell::~Spell()
{	
}
SpellTarget* Spell::getTargetFromCell(Cell* c) const
{
	if (_selector)
	{
		return _selector->getTargetFromCell(c);
	}
	return nullptr;
}
bool Spell::cast(unsigned int cell)
{
	SpellTarget* target = getTargetFromCell(GAMEINST->getGrid()->getCell(cell));
	if (target)
		return cast(target);	
	
	return false;
}
bool Spell::cast(SpellTarget* target)
{

	if (canCastOn(target))
	{
		_cooldown = _max_cooldown;
		_caster->removeCapaciyPoint(_cp_cost);
		_caster->removeMovementPoint(_mp_cost);
		_caster->lowerHitPoint(_hp_cost);

		for (Effect* e : _effects)
		{
			e->apply(target);
		}

		LOGINFO << _caster->getName() << " : Casting " << _name << " on ";
		target->displayBasic(LOGINFO);
		
		LOGINFO << endl;
		(new SpellEvents::SpellCastEvent(this))->dispatch();
		return true;
	}
	LOGWARN << _caster->getName() << " : Fail cast " << _name << endl;
	return false;
}
bool Spell::canCastOn(SpellTarget* target)
{
	if (_caster)
	{
		int distance = _caster->getDistance(*target);
		if (distance <= _max_scope && distance >= _min_scope)
		{
			if (_caster->getCP() >= _cp_cost)
			{
				if (_caster->getMP() >= _mp_cost)
				{
					if (_caster->getHP() >= _hp_cost)
					{
						if (!_is_inline || _caster->getCell()->isInLine(*target->getCell()))
						{
							if (_cooldown <= 0)
							{
								return true;
							}
							else
								LOGWARN << "Spell in cooldown" << endl;
						}
						else
							LOGWARN << "Target not inline" << endl;
					}
					else
						LOGWARN << "Not enough HP" << endl;
				}
				else
					LOGWARN << "Not enough MP" << endl;				
			}
			else
				LOGWARN << "Not enough CP" << endl;
		}
		else
			LOGWARN << "Not in scope" << endl;
	}
	return false;
}
void Spell::addEffect(Effect* effect)
{
	_effects.push_back(effect);
}
void Spell::beginTurn()
{
	if (_cooldown > 0)
		_cooldown--;
}
vector<unsigned int> Spell::getCellsInRange() const
{// TODO: add inline check
	Grid* grid = GAMEINST->getGrid();
	const Cell* casterCell = _caster->getCell();
	int x = casterCell->getPosX(), y = casterCell->getPosY();
	vector<unsigned int> ret;
	for (int i = -_max_scope; i <= _max_scope; i++)
	{
		for (int j = -_max_scope; j <= _max_scope; j++)
		{
			SpellTarget* target = grid->getCellAt(x + i, y + j);
			if (target)
			{
				int distance = _caster->getDistance(*target);
				if (distance <= _max_scope && distance >= _min_scope && (!_is_inline || casterCell->isInLine(*target->getCell())))
				{
					ret.push_back(target->getCell()->getNumber());
				}
			}
		}
	}
	return ret;
}

void Spell::setTargetSelector(TargetSelector* s)
{
	if (s != _selector)
	{
		if (_selector)
			delete _selector;
		_selector = s;
	}
}
ostream& operator<<(ostream& o, const Spell& s)
{
	o << "Displaying spell: " << s._name << endl;
	/* ... */
	return o;
}


