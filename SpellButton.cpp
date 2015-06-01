#include "SpellButton.h"
#include "SpellRecap.h"

SpellButton::SpellButton(int spellID, SpellRecap* recap)
	: Button(50, 50), _spell_id(spellID), _spell_recap(recap)
{
	auto clickLambda = [=](Event* e)
	{
		persistentSelect();
	};
	Clickable::setCallback(new EventCallback(clickLambda));

	int id;
	_spell_recap->getCharacter()->getType();
	if (_spell_recap->getCharacter()->getType() == "archer")
		id = 1;
	else if (_spell_recap->getCharacter()->getType() == "knight")
		id = 5;
	else
		id = 9;
	this->setBackground((*ServiceLocator::getTextureManager())["icon_spell_" + to_string(id+spellID)]);
	this->setHoverBackground((*ServiceLocator::getTextureManager())["icon_spell_" + to_string(id + spellID)]);
}


SpellButton::~SpellButton()
{
}


void SpellButton::onMouseIn(MotionEvent* e) 
{
	Button::onMouseIn(e);
	_spell_recap->selectSpell(_spell_id);
}
void SpellButton::onMouseOut(MotionEvent* e)
{
	Button::onMouseOut(e);

	if (!_selected_persistent)
	{
		_spell_recap->unselectSpell(_spell_id);		
	}
}
void SpellButton::persistentSelect()
{
	_selected_persistent = true;
}
void SpellButton::unselect()
{
	_selected_persistent = false; 
	_spell_recap->unselectSpell(_spell_id); 
}