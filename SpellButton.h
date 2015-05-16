#pragma once
#include "Button.h"
#include "GridOctopus.h"
class SpellRecap;

class SpellButton :
	public Button
{
public:
	SpellButton(int spellID, SpellRecap* spellRecap);
	virtual ~SpellButton();

	virtual void onMouseIn(MotionEvent* e) override;
	virtual void onMouseOut(MotionEvent* e) override;

	void unselect();
	void persistentSelect();

private:
	int _spell_id;
	SpellRecap* _spell_recap;

	bool _selected_persistent = false;
};

