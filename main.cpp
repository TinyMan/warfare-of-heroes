#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"
#include "ServiceLocator.h"
#include "Grid.h"
#include "Mage.h"

using namespace std;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	Game *g = new Game();
	Grid *grid = new Grid();
	Mage* mage = new Mage();

	ServiceLocator::getTimeService()->setTimeout(900, Callback(&Game::addGameObject, g, grid));

	g->addGameObject(mage);
	grid->setActive(false);
	mage->setActive(false);
	//grid->setActive();
	ServiceLocator::getTimeService()->setTimeout(2500, Callback(&Grid::setActive, grid, true));

	ServiceLocator::getTimeService()->setInterval(2000, Callback(&Game::displayState, g));

	ServiceLocator::getTimeService()->setTimeout(5000, Callback(&Game::stop, g));
	g->loop();


	delete g;

	cout << "Ending @ " << SDL_GetTicks() << endl;

	system("pause");
	SDL_Quit();
	return 0;
}
