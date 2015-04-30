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
	_nameLabel->setBackground(Texture(150, 50));

	_hp = new Label(150, 50, to_string(_character->getHP()), (*ServiceLocator::getFontManager())["Comic Sans MS"]);
	_hp->setTextAlignment(Alignment::CENTERX | Alignment::CENTERY);
	_hp->setBackground(Texture(150, 50));

	_pt = _hp->clone();
	_pt->setText(to_string(_character->getCP()));

	_pm = _hp->clone();
	_pm->setText(to_string(_character->getMP()));

	_hp_bar = new ProgressBar(150, 50);
	_hp_bar->setBackground(Texture(150, 50));
	_hp_bar->setValue(50);

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
}


RecapOctopus::~RecapOctopus()
{
}
