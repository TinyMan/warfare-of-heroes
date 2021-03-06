#pragma once
#include "Game.h"
#include "SDLEvents.h"
#include "Panel.h"
#include "Button.h"
#include "Octopus.h"
#include "GameObject.h"
#include "Character.h"
#include "Grid.h"
#include "Tooltip.h"
#include "GridOctopus.h"
#include "Chrono.h"
#include "RecapOctopus.h"
#include "Archer.h"
#include "Mage.h"
#include "Knight.h"
#include "SpellRecap.h"
#include "PlayerOctopus.h"
#include "ObstacleOctopus.h"


class MenuSelection : public Panel
{
public:
	MenuSelection();
	~MenuSelection();

	void selectClass(Character* c);
	void selectSpell(int x);
	void updateClass();
	void updateSpell();
	void updateIcone1();
	void updateIcone2();
	void ready();

	void clickArrow(char c);
	void updateShowSelect(string s);

private:
	Archer* a = nullptr;
	Knight* k = nullptr;
	Mage* m = nullptr;

	Character* _selected_class;
	int _selected_spell_id=0;

	Button* choiceJ1;
	Label* nameJ1;
	Button* choiceJ2;
	Label* nameJ2;

	// Classes :
	Label* nomClasse;
	Label* descrClasse;

	// Spells :
	Button* spell1;
	Button* spell2;
	Button* spell3;
	Button* spell4;
	Label* nomSpell;
	Label* descrSpell;
	Label* infos;

	// Selection :
	Button* button_selec_1;
	Character* j1 = nullptr;
	Character* j2 = nullptr;

	//For the Selection with Arrows
	int nbChoice = 0;
	Button* showSelectChar;


};

