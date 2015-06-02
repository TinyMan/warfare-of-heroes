#include "RecapOctopus.h"
#include "Game.h"
#include "ServiceLocator.h"


RecapOctopus::RecapOctopus(size_t characterID)
	: Panel(200, 600), _character(GAMEINST->getPlayer(characterID))
{
	
	//setBgColor(Color::BGCOLOR);
	Texture tata = (*ServiceLocator::getTextureManager())["fondcaca"];//Penser à changer le nom
	if (characterID == 1)
		tata = (*ServiceLocator::getTextureManager())["fondteub"]; //Penser à changer le nom
	setBackground(tata); //Penser à changer le nom

	_nameLabel = new Label(150, 50, _character->getName(), (*ServiceLocator::getFontManager())["LifeCraft"]);
	_nameLabel->setTextAlignment(Alignment::CENTERX | Alignment::CENTERY);

	_hp = new Label(150, 50, _character->getHPString(), (*ServiceLocator::getFontManager())["LifeCraft"]);
	_hp->setTextAlignment(Alignment::CENTERX | Alignment::CENTERY);


	_pt = new Label(150, 50, to_string(_character->getCP()), (*ServiceLocator::getFontManager())["LifeCraft"]);
	_pt->setTextAlignment(Alignment::CENTERX | Alignment::CENTERY);


	_pm = new Label(150, 50, to_string(_character->getMP()), (*ServiceLocator::getFontManager())["LifeCraft"]);
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
	Panel::update();
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
void RecapOctopus::internalRender(SDL_Renderer* r, bool force ) 
{
	if (isActive())
	{
		bool dirty = isDirty();
		bool d = (force || dirty);
		if (d)
		{

		}
	}
	Panel::internalRender(r, force);
}