#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"
#include "ServiceLocator.h"
#include "Grid.h"

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

	ServiceLocator::getTimeService()->setTimeout(900, Callback(&Game::addGameObject, g, grid));
	
	g->loop();


	delete g;
	cout << "Ending @ " << SDL_GetTicks() << endl;

	system("pause");
	SDL_Quit();
	return 0;
}
