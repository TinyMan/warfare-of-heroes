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
using namespace std;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	Game *g = Game::getInstance();

	LOGINFO << "Starting @ " << SDL_GetTicks() << endl;

	Grid* grid = g->getGrid();
	grid->generateObstacle();

	Archer* player1 = new Archer(0, 2);
	Mage* player3 = new Mage(6,2);
	g->addGameObject(grid, player1, player3);
	g->addPlayer(player1);
	g->addPlayer(player3);
	
	Panel* p = new Panel();
	Button* b = new Button(250, 250, 100, 100);
	Button* b1 = new Button(300, 300, 100, 100);
	ServiceLocator::getFontManager()->loadFont("Images/FNT/comic_sans_ms.fnt");
	Label* l = new Label(50, 50, 100, 100, "Salut", (*ServiceLocator::getFontManager())["Comic Sans MS"]);
	l->setTextColor(Color::RED);
	b1->setColor({ 0, 255, 0, 255 });
	b1->setZIndex(5);

	auto switcher = [=](Event*) 
	{
		
		int s = l->getTextSize();
		l->setTextSize(s + 2);
	};

	b->Clickable::setCallback(new EventCallback(&Game::stop, GAMEINST));
	b1->Clickable::setCallback(new EventCallback(switcher));

	
	p->add(b);
	p->add(b1);
	g->getOctopus()->setFrame(p);

	p->add(l);

	p->setBackground((*ServiceLocator::getTextureManager())["menu_mockup"]);
	b->setText("Bouton 1");
	b->setFont((*ServiceLocator::getFontManager())["Comic Sans MS"]);
	b->setTextColor(Color::GREEN);
	l->setTextSize(10);
	//g->stop();
	g->loop();

	LOGINFO << "Ending @ " << SDL_GetTicks() << endl;

	delete g;


	system("pause");
	SDL_Quit();

	return 0;
}
