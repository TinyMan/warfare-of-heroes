#include <SDL2/SDL.h>
#include "servicelocator.h"
#include "logservice.h"

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	ServiceLocator::provide(new LogService("log.txt"));
	SDL_Window *screen = SDL_CreateWindow("My Game Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		 SDL_WINDOW_OPENGL);
	ServiceLocator::getLog()->write(LogService::DEBUG, "Hello");
	SDL_Delay(5000);
	SDL_Quit();
	return 0;
}