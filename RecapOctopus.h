#pragma once
#include "Character.h"
#include "Panel.h"
#include "Label.h"
#include "ProgressBar.h"

class RecapOctopus :
	public Panel
{
public:
	RecapOctopus(size_t characterID);
	virtual ~RecapOctopus();

	// etc ...
	virtual bool concernMe(Event* e) const;
	void onEvent(Event* e);

protected:
	virtual void onLoseHP(LoseHpEvent* e);
	virtual void onLoseMP(LoseMPEvent* e);
	virtual void onLoseCP(LoseCPEvent* e);
	virtual void onGainCP(GainCPEvent* e);

	void updateHP() { _hp->setText(_character->getHPString()); _hp_bar->setValue(_character->getHPPercent()); }
	void updateMP() { _pm->setText(to_string(_character->getMP())); }
	void updateCP() { _pt->setText(to_string(_character->getCP())); }

private:
	Character* _character = nullptr;
	Label* _nameLabel = nullptr;
	Label* _pt = nullptr;
	Label* _pm = nullptr;
	Label* _hp = nullptr;
	ProgressBar* _hp_bar = nullptr;
};

