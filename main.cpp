#include <SDL2/SDL.h>
#include <iostream>
#include "Callback.h"
#include "Timeout.h"
#include "Interval.h"
#include "TimeService.h"

void myCallback(int a, TimeService* ts)
{
	cout << SDL_GetTicks() << "\ta = " << a  << endl;
	//ts->setTimeout(1000, Callback(myCallback, 1, ts));
}
void doit(TimeService* ts)
{
	ts->setTimeout(1000, Callback(myCallback, 1, ts));
	ts->setInterval(1000, Callback(myCallback, 1, ts));
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	cout << "Starting @ " << SDL_GetTicks() << endl;
	TimeService *ts = new TimeService();
	doit(ts);
	while (SDL_GetTicks() < 5000)
	{
		SDL_Delay(100);
		ts->update();
	}
	cout << "Ending @ " << SDL_GetTicks() << endl;
	delete ts;
	system("pause");
	SDL_Quit();
	return 0;
}
