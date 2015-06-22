#include "SpellRecap.h"
#include "GridOctopus.h"
#include "ServiceLocator.h"

SpellRecap::SpellRecap(Character* c, GridOctopus* grid)
	: _character(c), Panel(1200, 300), _grid(grid), spells(_character->getSpells())
{
	createSpellButtons();

	_selected_spell_name = new Label(250, 50);
	_selected_spell_name->setTextAlignment(Alignment::CENTERX | Alignment::CENTERY);
	add(_selected_spell_name, Alignment::TOP | Alignment::RIGHT);
	_selected_spell_name->setPositionY(20);

	_selected_spell_description = new Label(900, 180);
	_selected_spell_description->setTextAlignment(Alignment::LEFT | Alignment::CENTERY);
	add(_selected_spell_description, 150, 100 );

	//setBgColor(Color::BGCOLOR);
	Texture bgTexture = (*ServiceLocator::getTextureManager())["bgSpells"];//Penser à changer le nom
	setBackground(bgTexture);


	EVENTSERVICE->listen(typeid(BeginTurnEvent), [=](Event* e) { 
		setActive(_character == GAMEINST->getCurrentPlayer()); 
		unselectSpell(_selected_spell); 
	});
	EVENTSERVICE->listen(typeid(CellClick), [=](Event* e) { 
		CellClick* ev = dynamic_cast<CellClick*>(e); 
		if (ev)
		{
			if (ev->button == SDL_BUTTON_LEFT)
				clickOnCell(ev->cellNumber);
			else
				unselectSpell(_selected_spell);
		}
	});
	EVENTSERVICE->listen(typeid(CellHover), [=](Event* e) { 
		CellHover* ev = dynamic_cast<CellHover*>(e);
		if (ev)
			hoverCell(ev->cellPtr); 
	});
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
		for (auto& e : _label_spells)
		{
			e.second->setText(to_string(spells[e.first]->getCPCost()) + " CP");
		}
		for (auto& e : _label_cooldown)
		{
			int cd = spells[e.first]->getCooldown();
			if (cd > 0)
			{
				e.second->setText(to_string(cd) + " turn");
				_buttons_spells[e.first]->setEnabled(false);
			}
			else
			{
				e.second->setText("Usable !");
				_buttons_spells[e.first]->setEnabled(true);
			}
		}
		if (spells.count(_selected_spell) == 1)
		{
			_selected_spell_name->setText(spells[_selected_spell]->getName());
			_selected_spell_description->setText(spells[_selected_spell]->getDescription());
		}
	}
	
}
void SpellRecap::createSpellButtons()
{
	if (_character == nullptr)
		return;
	const int START_X = 200;
	const int START_Y = SpellButton::HEIGHT;
	const int SPACING = 100;

	for (auto& spell : _character->getSpells())
	{
		// creation of button
		_buttons_spells[spell.first] = new SpellButton(spell.first, this);

		// creation of labels (next to button)
		_label_spells[spell.first] = new Label(SPACING, SpellButton::HEIGHT);
		_label_spells[spell.first]->setPadding(10);
		_label_spells[spell.first]->setTextAlignment(Alignment::LEFT | Alignment::CENTERY);

		_label_cooldown[spell.first] = new Label(SpellButton::WIDTH*2, SpellButton::HEIGHT);
		_label_cooldown[spell.first]->setTextAlignment(Alignment::LEFT | Alignment::BOTTOM);
	}

	/* add of buttons */
	int x = START_X;
	int y = START_Y;
	for (auto b : _buttons_spells)
	{
		add(b.second, x, y);
		x += SpellButton::WIDTH + SPACING;
	}

	/* add of labels */
	x = START_X + SpellButton::WIDTH;
	for (auto b : _label_spells)
	{
		add(b.second, x, y);
		x += SpellButton::WIDTH + SPACING;
	}

	/* add of labels */
	x = START_X;
	y = 0;
	for (auto b : _label_cooldown)
	{
		add(b.second, x, y);
		x += SpellButton::WIDTH + SPACING;
	}
}
void SpellRecap::selectSpell(int spellID)
{
	if (spellID != _selected_spell)
	{
		if (spells.count(_selected_spell) == 1)
			_buttons_spells[_selected_spell]->unselect();

		_selected_spell = spellID;
		_selected_spell_range = _character->getSpell(_selected_spell)->getCellsInRange();
		_grid->mark(_selected_spell_range, range_color);

		setDirty();
	}
}
void SpellRecap::unselectSpell(int spellID)
{
	if (spellID == _selected_spell &&spells.count(_selected_spell) == 1)
	{
		_grid->unmark(_selected_spell_range);
		_grid->unmark(_selected_spell_aoe);
		_selected_spell_range.clear();
		_selected_spell_aoe.clear();
		_selected_spell = NO_SPELL;
		setDirty();
	}
}
void SpellRecap::clickOnCell(unsigned int c)
{
	if (!isActive())
		return;
	if (spells.count(_selected_spell) == 1)
	{
		spells[_selected_spell]->cast(c);
		unselectSpell(_selected_spell);
	}
	else
	{
		GAMEINST->getCurrentPlayer()->move(c);
	}
}
void SpellRecap::hoverCell(Cell* c)
{
	if (!isActive() || !c || _hovered_cell == c)
		return;
	if (_hovered_cell && find(_selected_spell_range.begin(), _selected_spell_range.end(), _hovered_cell->getNumber()) != _selected_spell_range.end())
		_grid->unmark(_hovered_cell->getNumber());

	_grid->unmark(_selected_spell_aoe);
	_grid->mark(_selected_spell_range, range_color);

	if (find(_selected_spell_range.begin(), _selected_spell_range.end(), c->getNumber()) != _selected_spell_range.end())
	{		
		list<Cell* > cells = spells[_selected_spell]->getTargetFromCell(c)->getCells();
		_selected_spell_aoe.clear();
		for (Cell* c : cells)
			_selected_spell_aoe.push_back(c->getCell()->getNumber());
		_grid->mark(_selected_spell_aoe, range_hover_color);
	}
	else
	{
		//_grid->mark(c->getNumber(), Color::BLUE);
	}

	_hovered_cell = c;
}
void SpellRecap::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = force || isDirty();
		if (d)
		{

		}
	}
	Panel::internalRender(r, force);

}