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

using namespace std;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	

	Game *g = Game::getInstance();

	LOGINFO << "Starting @ " << SDL_GetTicks() << endl;

	Grid* grid = g->getGrid();
	grid->generateObstacle();

	Archer* player1 = new Archer(0, 2);
	Mage* player3 = new Mage(6,2);
	g->addGameObject(grid, player1, player3);
	g->addPlayer(player1);
	g->addPlayer(player3);
	
	player1->setToDelete();
	auto lambda = [](Event*) { GAMEINST->stop(); };
	auto lambda1 = [](Event*) { LOGINFO << "Hover on my button ! " << endl; };
	Button* b = new Button(250,250,100,50);
	b->Clickable::setCallback(new EventCallback(lambda));
	g->getOctopus()->addBaby(b);
	//g->stop();
	/*g->displayState();	
	g->start();
	while (g->isRunning())
	{
		g->handleUserInput();
		g->displayState(LOGINFO);
		// TODO : add textmode gameplay
	}*/
	g->loop();

	LOGINFO << "Ending @ " << SDL_GetTicks() << endl;

	delete g;


	system("pause");
	SDL_Quit();

	return 0;
}
