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
	Grid *grid = new Grid();
	Archer* player1 = new Archer();
	Knight* player2 = new Knight();
	Mage* player3 = new Mage();

	g->addGameObject(grid, player1, player2);
	g->displayState();
	grid->generateObstacle();
	grid->setObject(player1, 0, 0);
	grid->setObject(player2, Grid::WIDTH-1, Grid::HEIGHT-1);

	player1->cast(Archer::VOLLEY, player2);
	player2->cast(Knight::SWORD_DESTINY, player3);
	player3->cast(Mage::FIREBALL, player1);
	player3->cast(Mage::ERUPTION, grid->getCellAt(2, 3));
	LOGINFO << "Grid: " << endl;
	grid->display(LOGINFO);

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
