#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"
#include "ServiceLocator.h"
#include "Grid.h"
#include "Mage.h"
#include "Knight.h"

using namespace std;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	

	Game *g = new Game();

	LOGINFO << "Starting @ " << SDL_GetTicks() << endl;
	Grid *grid = new Grid();
	Mage* player1 = new Mage();
	Knight* player2 = new Knight();

	g->addGameObject(grid, player1, player2);
	g->displayState();

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
