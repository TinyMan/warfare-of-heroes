#include <SDL2/SDL.h>
#include <iostream>
#include "ServiceLocator.h"

void myCallback(int a, TimeService* ts)
{
	cout << SDL_GetTicks() << "\ta = " << a  << endl;
}


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	cout << "Starting @ " << SDL_GetTicks() << endl;
	ServiceLocator::provide(new TimeService());
	ServiceLocator::provide(new LogService("log.txt"));
	
	ServiceLocator::getTimeService()->setTimeout(1000, Callback(myCallback, 1, ServiceLocator::getTimeService()));
	while (SDL_GetTicks() < 5000)
	{
		SDL_Delay(100);
		ServiceLocator::getTimeService()->update();
	}
	cout << "Ending @ " << SDL_GetTicks() << endl;

	system("pause");
	SDL_Quit();
	return 0;
}
