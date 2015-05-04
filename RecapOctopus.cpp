#include "RecapOctopus.h"
#include "Game.h"
#include "ServiceLocator.h"


RecapOctopus::RecapOctopus(size_t characterID)
	: Panel(200, 600), _character(GAMEINST->getPlayer(characterID))
{
	if(characterID & 1)
		setBackground(Texture(200, 600, Color::WHITE));
	else
		setBackground(Texture(200, 600, Color::BLUE));

	_nameLabel = new Label(150, 50, _character->getName(), (*ServiceLocator::getFontManager())["Comic Sans MS"]);
	_nameLabel->setTextAlignment(Alignment::CENTERX | Alignment::CENTERY);

	_hp = new Label(150, 50, _character->getHPString(), (*ServiceLocator::getFontManager())["Comic Sans MS"]);
	_hp->setTextAlignment(Alignment::CENTERX | Alignment::CENTERY);


	_pt = new Label(150, 50, to_string(_character->getCP()), (*ServiceLocator::getFontManager())["Comic Sans MS"]);
	_pt->setTextAlignment(Alignment::CENTERX | Alignment::CENTERY);


	_pm = new Label(150, 50, to_string(_character->getMP()), (*ServiceLocator::getFontManager())["Comic Sans MS"]);
	_pm->setTextAlignment(Alignment::CENTERX | Alignment::CENTERY);

	_hp_bar = new ProgressBar(150, 50);
	_hp_bar->setValue(_character->getHPPercent());

	add(_nameLabel, Alignment::TOP | Alignment::CENTERX);
	_nameLabel->setPositionY(50);
	add(_hp_bar, Alignment::BOTTOM | Alignment::CENTERX);
	_hp_bar->setPositionY(500);
	add(_hp, Alignment::BOTTOM | Alignment::CENTERX);
	_hp->setPositionY(400);
	add(_pt, Alignment::BOTTOM | Alignment::CENTERX);
	_pt->setPositionY(300);
	add(_pm, Alignment::BOTTOM | Alignment::CENTERX);
	_pm->setPositionY(200);
	// TODO: bind to internal events (character events) to receive changes to the data (hp, mp, pt...)
	ServiceLocator::getEventService()->listen(typeid(LoseCPEvent), EventCallback(&RecapOctopus::onEvent, this));
	ServiceLocator::getEventService()->listen(typeid(LoseHpEvent), EventCallback(&RecapOctopus::onEvent, this));
	ServiceLocator::getEventService()->listen(typeid(LoseMPEvent), EventCallback(&RecapOctopus::onEvent, this));
	ServiceLocator::getEventService()->listen(typeid(GainCPEvent), EventCallback(&RecapOctopus::onEvent, this));
	ServiceLocator::getEventService()->listen(typeid(GainHPEvent), EventCallback(&RecapOctopus::onEvent, this));
	ServiceLocator::getEventService()->listen(typeid(GainMPEvent), EventCallback(&RecapOctopus::onEvent, this));
}


RecapOctopus::~RecapOctopus()
{
}

void RecapOctopus::update()
{
	updateCP();
	updateHP();
	updateMP();

}
void RecapOctopus::onLoseHP(LoseHpEvent* e)
{
	updateHP();
}
void RecapOctopus::onLoseMP(LoseMPEvent* e)
{
	updateMP();
}
void RecapOctopus::onLoseCP(LoseCPEvent* e)
{
	updateCP();
}
void RecapOctopus::onGainCP(GainCPEvent* e)
{
	updateCP();
}
bool RecapOctopus::concernMe(Event* e) const
{
	if (CharacterEvent* ev = dynamic_cast<CharacterEvent*>(e))
	{
		return ev->getCharacter() == _character;
	}
	return false;
}
void RecapOctopus::onEvent(Event* e)
{
	if (concernMe(e))
	{
	//	LOGINFO << "RecapOctopus got an event" << endl;
		if (LoseCPEvent* ev = dynamic_cast<LoseCPEvent*>(e))
			onLoseCP(ev);
		if (LoseHpEvent* ev = dynamic_cast<LoseHpEvent*>(e))
			onLoseHP(ev);
	}
}