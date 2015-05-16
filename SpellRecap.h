#pragma once
#include <map>
#include "Panel.h"
#include "Spell.h"
#include "SpellButton.h"
#include "Label.h"
class Character;
class GridOctopus;

#define NO_SPELL 9999

using namespace std;

class SpellRecap :
	public Panel
{
public:
	SpellRecap(Character* c, GridOctopus* grid);
	virtual ~SpellRecap();
		
	virtual void update();

	void selectSpell(int spellID);
	void unselectSpell(int spellID);

private:
	GridOctopus* _grid = nullptr;
	Character* _character = nullptr;
	map<int, SpellButton*> _buttons_spells;
	map<int, Label*> _label_spells;
	map<int, Spell*>  spells;

	Label* _selected_spell_name = nullptr;
	Label* _selected_spell_description = nullptr;

	int _selected_spell = NO_SPELL;

	void createSpellButtons();

};

