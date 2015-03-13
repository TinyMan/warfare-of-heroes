#include <SDL2/SDL.h>
#include <iostream>
#include "Callback.h"
#include "Timeout.h"

void myCallback(int a, int b, char c)
{
	cout << SDL_GetTicks() << "\ta = " << a  << c << endl;
}
template <typename ...Args>
void tt(void f(Args...), Args... args)
{
	f(args...);
}
int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	cout << "Starting timeout @ " << SDL_GetTicks() << endl;
	Timeout* to = new Timeout(4000, new Callback(myCallback, 1, 2, 'c'));
	while (SDL_GetTicks() < 5000)
	{
		SDL_Delay(100);

		to->check();
	}
	SDL_Delay(10000);
	SDL_Quit();
	return 0;
}
