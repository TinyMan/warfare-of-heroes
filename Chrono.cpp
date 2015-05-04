#include "Chrono.h"
#include "Game.h"
#include "ServiceLocator.h"
#include "Character.h"

Chrono::Chrono()
	: Button(300, 100)
{
	setText("xxx's turn\nTime left: xx sec");
	setTextAlignment(Alignment::CENTERX | Alignment::CENTERY);
	auto l = [=](Event*) { GAMEINST->endTurn(); };
	Clickable::setCallback(new EventCallback(l));
}


Chrono::~Chrono()
{
}
void Chrono::update()
{
	setText(GAMEINST->getCurrentPlayer()->getName() + "'s turn\n"
		"Time left: " + to_string(GAMEINST->getTimeLeft() / 1000 )+ " seconds");
}
