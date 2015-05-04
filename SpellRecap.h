#pragma once
#include <map>
#include "Panel.h"
#include "Spell.h"
#include "Button.h"
#include "Label.h"
class Character;

using namespace std;

class SpellRecap :
	public Panel
{
public:
	SpellRecap(Character* c);
	virtual ~SpellRecap();
		
	virtual void update();

private:
	Character* _character = nullptr;
	map<int, Button*> _buttons_spells;
	Label* _selected_spell_name = nullptr;
	Label* _selected_spell_description = nullptr;

	int _selected_spell = 0;

	void createSpellButtons();

};

