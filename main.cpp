#include <SDL2/SDL.h>
#include <iostream>
#include "Event.h"
#include "ServiceLocator.h"

using namespace std;

void myCallback( int a)
{
	cout << SDL_GetTicks() << "\ta = " << a  << endl;

}


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	cout << "Starting @ " << SDL_GetTicks() << endl;
	ServiceLocator::provide(new EventService);
	ServiceLocator::getEventService()->listen(Event::LAND, Callback(myCallback, 1));
	Event e(Event::LAND);
	SDL_Delay(1000);
	ServiceLocator::getEventService()->dispatch(e);
//	e.dispatch();

	cout << "Type: " << e.getType() << endl;
	cout << "Ending @ " << SDL_GetTicks() << endl;

	system("pause");
	SDL_Quit();
	return 0;
}
