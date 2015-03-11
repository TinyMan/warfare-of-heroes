#include <SDL2/SDL.h>
#include "logservice.h"

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	LogService log("log.txt");
	SDL_Window *screen = SDL_CreateWindow("My Game Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		 SDL_WINDOW_OPENGL);
	log.write(LogService::DEBUG, "Hello");
	SDL_Delay(5000);
	SDL_Quit();
	return 0;
}