#include <iostream>
#include "Game.h"
#include "ServiceLocator.h"
#include <SDL2/SDL_mixer.h>

using namespace std;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	//Initialize SDL_mixer
	Mix_Init(MIX_INIT_FLAC |
		MIX_INIT_MOD |
		MIX_INIT_MP3 |
		MIX_INIT_OGG);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	srand((unsigned int)time(NULL));
	Game *g = Game::getInstance();

	LOGINFO << "Starting @ " << SDL_GetTicks() << endl;
	g->initialize();

	g->loop();

	LOGINFO << "Ending @ " << SDL_GetTicks() << endl;

	delete g;


	//system("pause");
	Mix_Quit(); 
	SDL_Quit();


	return 0;
}
