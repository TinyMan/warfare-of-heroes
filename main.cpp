#include <SDL2/SDL.h>
#include <iostream>
#include "Callback.h"
#include "Timeout.h"
#include "Interval.h"

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
	
	cout << "Starting @ " << SDL_GetTicks() << endl;
	Interval *iv = new Interval(1000, new Callback(myCallback, 1, 2, 'c'));
	cout << "Iv started @ " << iv->getStartTime() << endl;
	while (SDL_GetTicks() < 5000)
	{
		cout << "next time @ " << iv->getNextTriggerTime() << endl;
		SDL_Delay(100);
		iv->check();
	}
	cout << "Ending @ " << SDL_GetTicks() << endl;
	SDL_Delay(10000);
	SDL_Quit();
	return 0;
}
