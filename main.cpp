#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"
#include "ServiceLocator.h"

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
	
	ServiceLocator::getTimeService()->setTimeout(900, Callback(&Game::addGameObject, g, nullptr));
	
	g->loop();


	delete g;
	cout << "Ending @ " << SDL_GetTicks() << endl;

	system("pause");
	SDL_Quit();
	return 0;
}
