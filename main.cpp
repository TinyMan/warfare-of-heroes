#include <iostream>
#include "Game.h"
#include "ServiceLocator.h"

using namespace std;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	Game *g = Game::getInstance();

	LOGINFO << "Starting @ " << SDL_GetTicks() << endl;
	g->initialize();

	g->loop();

	LOGINFO << "Ending @ " << SDL_GetTicks() << endl;

	delete g;


	system("pause");
	SDL_Quit();

	return 0;
}
