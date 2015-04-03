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

using namespace std;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	

	Game *g = Game::getInstance();

	LOGINFO << "Starting @ " << SDL_GetTicks() << endl;

	Grid* grid = g->getGrid();
	grid->generateObstacle();

	Knight* player1 = new Knight(0,2);
	Mage* player3 = new Mage(6,2);
	g->addGameObject(grid, player1, player3);
	g->addPlayer(player1);
	g->addPlayer(player3);
	
	player1->setToDelete();
	//g->stop();
	g->displayState();	
	g->start();
	while (g->isRunning())
	{
		g->handleUserInput();
		g->displayState(LOGINFO);
		// TODO : add textmode gameplay
	}

	LOGINFO << "Ending @ " << SDL_GetTicks() << endl;

	delete g;


	system("pause");
	SDL_Quit();

	return 0;
}
