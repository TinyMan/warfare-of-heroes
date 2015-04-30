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
#include "Polygon.h"
#include "Geometry.h"
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

	Point p1(0, 0);
	Point p2(25, 0);
	Point p3(25, 25);
	Point p4(0, 25);
		

	Polygon p;
	p.addPoint(p1);
	p.addPoint(p2);
	p.addPoint(p3);
	p.addPoint(p4);
	vector<Line> lines = p.getLines();
	for (auto l : lines)
	{
		cout << l << endl;
	}
	cout << "Intersection: " << lines[1].intersection(lines[2]) << endl;
	

	g->stop();
	g->loop();

	LOGINFO << "Ending @ " << SDL_GetTicks() << endl;

	delete g;


	system("pause");
	SDL_Quit();

	return 0;
}
