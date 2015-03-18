#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"
#include "ServiceLocator.h"
#include "Grid.h"
#include "Mage.h"

using namespace std;

void myCallback()
{
	cout << SDL_GetTicks() << "\ta = " << 1  << endl;

}


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	cout << "Starting @ " << SDL_GetTicks() << endl;
	
	Game *g = new Game();
	Grid *grid = new Grid();
	Mage* mage = new Mage();

	ServiceLocator::getTimeService()->setTimeout(900, Callback(&Game::addGameObject, g, grid));

	g->addGameObject(mage);
	mage->setActive(false);
	ServiceLocator::getTimeService()->setTimeout(2000, Callback(&Grid::setActive, grid, false));

	ServiceLocator::getTimeService()->setInterval(1000, Callback(&Game::displayState, g));
	g->loop();


	delete g;
	cout << "Ending @ " << SDL_GetTicks() << endl;

	system("pause");
	SDL_Quit();
	return 0;
}
