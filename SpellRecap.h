#pragma once
#include <map>
#include "Panel.h"
#include "Spell.h"
#include "SpellButton.h"
#include "Label.h"
#include "GridEvents.h"
class Character;
class GridOctopus;

#define NO_SPELL 9999

using namespace std;
using namespace Events::GridEvents;

class SpellRecap :
	public Panel
{
public:
	SpellRecap(Character* c, GridOctopus* grid);
	virtual ~SpellRecap();
		
	virtual void update();

	void selectSpell(int spellID);
	void unselectSpell(int spellID);
	Character* getCharacter() const { return _character; };

	virtual void clickOnCell(unsigned int c);
	virtual void hoverCell(Cell* c);

	const Color range_color = Color(0, 255, 0, 128);
	const Color range_hover_color = Color(255, 0, 0, 128);

protected:
	virtual void internalRender(SDL_Renderer* r, bool force = false) override;
private:
	GridOctopus* _grid = nullptr;
	Character* _character = nullptr;
	map<int, SpellButton*> _buttons_spells;
	map<int, Label*> _label_spells;
	map<int, Spell*>  spells;

	Label* _selected_spell_name = nullptr;
	Label* _selected_spell_description = nullptr;
	vector<unsigned int> _selected_spell_range;
	vector<unsigned int> _selected_spell_aoe;

	int _selected_spell = NO_SPELL;

	Cell* _hovered_cell = nullptr;

	void createSpellButtons();

};

