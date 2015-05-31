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
private:
	Character* _selected_class = new Archer();
	int _selected_spell_id;
	
	Label* nomClasse;
	Label* descrClasse;

	Button* spell1;
	Button* spell2;
	Button* spell3;
	Button* spell4;
	Label* nomSpell;
	Label* descrSpell;
	Label* infos;


};

