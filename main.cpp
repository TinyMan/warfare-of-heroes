#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"
#include "ServiceLocator.h"
#include "Grid.h"
#include "Mage.h"
#include "Knight.h"
#include "Archer.h"
#include "Spell.h"

using namespace std;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	

	Game *g = Game::getInstance();

	LOGINFO << "Starting @ " << SDL_GetTicks() << endl;

	Grid* grid = g->getGrid();
	grid->generateObstacle();

	Archer* player1 = new Archer(0,0);
	Knight* player3 = new Knight(1, 0);
	g->addGameObject(grid, player1, player3);
	g->addPlayer(player1);
	g->addPlayer(player3);
	

	g->displayState();

	player1->beginTurn();
	Spell* av = new Spell("Arrow Volley", player1, 4, 120, 0, 10, 0, 8);
	av->cast(Character::targetSelector());
	g->displayState();
	//LOGINFO << *av << endl;

	/*g->start();
	while (g->isRunning())
	{
		g->handleUserInput();
		g->displayState(LOGINFO);
		// TODO : add textmode gameplay
	}*/

	LOGINFO << "Ending @ " << SDL_GetTicks() << endl;

	delete g;


	system("pause");
	SDL_Quit();

	return 0;
}
