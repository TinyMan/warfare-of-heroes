#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *screen = SDL_CreateWindow("My Game Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		 SDL_WINDOW_OPENGL);

	SDL_Delay(5000);
	SDL_Quit();
	return 0;
}