#include <SDL2/SDL.h>
#include <typeinfo>
#include <iostream>
#include "Game.h"
#include "ServiceLocator.h"
#include "Grid.h"
#include "Mage.h"
#include "Knight.h"
#include "Archer.h"
#include "Spell.h"
#include "SquareAoE.h"
#include "DiamondAoE.h"
#include "DamageEffect.h"
#include "LineAoE.h"
#include "Button.h"
#include "Panel.h"
#include "Font.h"
#include "Label.h"
#include "Line.h"
using namespace std;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	Game *g = Game::getInstance();

	LOGINFO << "Starting @ " << SDL_GetTicks() << endl;
	g->initialize();
	
	/*Grid* grid = g->getGrid();
	grid->generateObstacle();

	Archer* player1 = new Archer(0, 2);
	Mage* player3 = new Mage(6,2);
	g->addGameObject(grid, player1, player3);
	g->addPlayer(player1);
	g->addPlayer(player3);*/

	Line l1(1, 2, 5, 7);
	Line l2(3, 3, 4, 5);
	cout << l1 << endl << l2 << endl;
	cout << "Intersection: " << l1.intersection(l2) << endl;
	cout << "Intersection x: " << l1.intersectX(l2) << endl;
	cout << "Intersection y: " << l1.intersectY(l2) << endl;
	g->stop();
	g->loop();

	LOGINFO << "Ending @ " << SDL_GetTicks() << endl;

	delete g;


	system("pause");
	SDL_Quit();

	return 0;
}
