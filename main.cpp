#include <SDL2/SDL.h>
#include <typeinfo>
#include <iostream>
#include "Game.h"
#include "ServiceLocator.h"
#include "Grid.h"
#include "Mage.h"
#include "Knight.h"
#include "Archer.h"
#include "Spell.h"
#include "SquareAoE.h"
#include "DiamondAoE.h"
#include "DamageEffect.h"
#include "LineAoE.h"
#include "Button.h"
#include "Panel.h"
#include "Font.h"
using namespace std;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Font f("Comic Sans MS", "Images/FNT/comic_sans_ms.fnt");
	cout << f << endl;
	system("pause");
	exit(0);

	Game *g = Game::getInstance();

	LOGINFO << "Starting @ " << SDL_GetTicks() << endl;

	Grid* grid = g->getGrid();
	grid->generateObstacle();

	Archer* player1 = new Archer(0, 2);
	Mage* player3 = new Mage(6,2);
	g->addGameObject(grid, player1, player3);
	g->addPlayer(player1);
	g->addPlayer(player3);
	
	Panel* p = new Panel();
	Button* b = new Button(250, 250, 100, 100);
	Button* b1 = new Button(300, 300, 100, 100);
	b1->setColor({ 0, 255, 0, 0 });
	b1->setZIndex(5);

	auto lambda = [](Event*) { GAMEINST->stop(); };
	auto switcher = [=](Event*) 
	{
		int t = b1->getZIndex();
		b1->setZIndex(b->getZIndex());
		b->setZIndex(t);
	};

	b->Clickable::setCallback(new EventCallback(lambda));
	b1->Clickable::setCallback(new EventCallback(switcher));

	
	p->add(b);
	p->add(b1);
	g->getOctopus()->addBaby(p);
	//g->getOctopus()->addBaby(b1);

	g->loop();

	LOGINFO << "Ending @ " << SDL_GetTicks() << endl;

	delete g;


	system("pause");
	SDL_Quit();

	return 0;
}
