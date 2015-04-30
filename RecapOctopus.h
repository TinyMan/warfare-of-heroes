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

private:
	Character* _character = nullptr;
	Label* _nameLabel = nullptr;
	Label* _pt = nullptr;
	Label* _pm = nullptr;
	Label* _hp = nullptr;
	ProgressBar* _hp_bar = nullptr;
};

