#include <SDL2/SDL.h>
#include <iostream>
#include "Callback.h"


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
	
	//tt(myCallback, 1, 2);
	//Callback<int, int, char> *cb = new Callback<int, int, char>(myCallback, 1, 2, 'c');
	Callback * cb = new Callback(myCallback, 1, 2, 'c');
	cb->call();
	/*
	while (SDL_GetTicks() < 5000)
	{
		SDL_Delay(100);

		ts.update();
	}*/
	SDL_Delay(10000);
	SDL_Quit();
	return 0;
}
