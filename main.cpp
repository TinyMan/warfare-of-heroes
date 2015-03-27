#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"
#include "ServiceLocator.h"
#include "Grid.h"
#include "Mage.h"
#include "Knight.h"
#include "Archer.h"

using namespace std;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	

	Game *g = Game::getInstance();

	LOGINFO << "Starting @ " << SDL_GetTicks() << endl;

	Grid* grid = g->getGrid();
	grid->generateObstacle();

	Archer* player1 = new Archer(0,0);
	Mage* player2 = new Mage(Grid::WIDTH - 1, Grid::HEIGHT - 1);
	g->addGameObject(grid, player1, player2);
	g->addPlayer(player1);
	g->addPlayer(player2);

	g->displayState();
	g->start();
	while (g->isRunning())
	{
		g->handleUserInput();
		// TODO : add textmode gameplay
	}

	LOGINFO << "Ending @ " << SDL_GetTicks() << endl;

	delete g;


	system("pause");
	SDL_Quit();

	return 0;
}
