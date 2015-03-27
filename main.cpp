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
	Archer* player1 = new Archer();
	Knight* player2 = new Knight();
	Mage* player3 = new Mage();

	g->addGameObject(grid, player1, player2);
	g->addPlayer(player1);
	g->addPlayer(player2);
	g->displayState();
	grid->generateObstacle();

	/*
	Callback quit(&Game::stop, g);
	Callback cb(&Archer::cast, player1, Archer::DMG_BUFF);

	UI->addAction(Action(quit, "Quit"));
	UI->addAction(Action(cb, "Cast damage buff"));

	auto lambda = [] (void* d){ LOGINFO << "Salut !!!!!!!" << endl; };
	Callback rofl(lambda);
	rofl.call();
	*/
	//g->stop();
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
