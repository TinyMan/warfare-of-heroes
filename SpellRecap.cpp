#include "SpellRecap.h"


SpellRecap::SpellRecap(Character* c)
	: _character(c), Panel(1200, 300)
{
	createSpellButtons();
	_selected_spell_name = new Label(200, 50);
	_selected_spell_name->setBgColor(Color::RED);
	add(_selected_spell_name, Alignment::TOP | Alignment::RIGHT);
}


SpellRecap::~SpellRecap()
{
}

void SpellRecap::update()
{
	Panel::update();

}
void SpellRecap::createSpellButtons()
{
	if (_character == nullptr)
		return;
	for (auto& spell : _character->getSpells())
	{
		_buttons_spells[spell.first] = new Button(50, 50);
		_buttons_spells[spell.first]->setBgColor(Color::GREEN);
	}
	int x = 150;
	int y = 15;
	for (auto b : _buttons_spells)
	{
		add(b.second, x, y);
		x += 50 + 35;
	}
}