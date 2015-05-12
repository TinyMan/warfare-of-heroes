#include "SpellRecap.h"


SpellRecap::SpellRecap(Character* c)
	: _character(c), Panel(1200, 300)
{
	createSpellButtons();

	_selected_spell_name = new Label(250, 50);
	_selected_spell_name->setTextAlignment(Alignment::CENTERX | Alignment::CENTERY);
	add(_selected_spell_name, Alignment::TOP | Alignment::RIGHT);
	_selected_spell_name->setPositionY(20);

	_selected_spell_description = new Label(900, 180);
	_selected_spell_description->setTextAlignment(Alignment::CENTERX | Alignment::CENTERY);
	add(_selected_spell_description, 150, 100 );

	setBgColor(Color::BGCOLOR);
}


SpellRecap::~SpellRecap()
{
	// TODO: delete
}

void SpellRecap::update()
{
	setActive(_character == GAMEINST->getCurrentPlayer());
	if (isActive())
	{
		Panel::update();
		map<int, Spell*>  spells = _character->getSpells();
		for (auto& e : _label_spells)
		{
			e.second->setText(to_string(spells[e.first]->getCPCost()) + " CP");
		}
		_selected_spell_name->setText(spells[_selected_spell]->getName());
		_selected_spell_description->setText(spells[_selected_spell]->getDescription());
	}
}
void SpellRecap::createSpellButtons()
{
	if (_character == nullptr)
		return;
	auto selectSpellLambda = [=](int id, Event* e)
	{
		selectSpell(id);
	};
	for (auto& spell : _character->getSpells())
	{
		// creation of button
		_buttons_spells[spell.first] = new Button(50, 50);
		_buttons_spells[spell.first]->Clickable::setCallback(new EventCallback(selectSpellLambda, spell.first));

		// creation of labels (next to button)
		_label_spells[spell.first] = new Label(100, 50);
		_label_spells[spell.first]->setPadding(10);
		_label_spells[spell.first]->setTextAlignment(Alignment::LEFT | Alignment::CENTERY);
	}

	/* add of buttons */
	int x = 150;
	int y = 20;
	for (auto b : _buttons_spells)
	{
		add(b.second, x, y);
		x += 50 + 100;
	}

	/* add of labels */
	x = 200;
	for (auto b : _label_spells)
	{
		add(b.second, x, y);
		x += 50 + 100;
	}
}
void SpellRecap::selectSpell(int spellID)
{
	if (spellID != _selected_spell)
	{
		_selected_spell = spellID;
		setDirty();
	}
}