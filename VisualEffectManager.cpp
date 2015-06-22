#include "VisualEffectManager.h"
#include "Spell.h"
#include "FireBallOctopus.h"


VisualEffectManager::VisualEffectManager()
{
	EVENTSERVICE->listen(typeid(SpellCastEvent), EventCallback(&VisualEffectManager::onCast, this));
	
}


VisualEffectManager::~VisualEffectManager()
{
}


void VisualEffectManager::onCast(Event* e)
{
	SpellCastEvent *ev = dynamic_cast<SpellCastEvent*>(e);
	if (ev) // check if event is a SpellCastEvent
	{
		Spell* spell = ev->spell;
		Character* caster = spell->getCaster();
		SpellTarget* target = ev->target;

		OctopusBaby* so = createSpellOctopus(spell, caster, target);

		_effectContainer->add(so);
	}
}

OctopusBaby* VisualEffectManager::createSpellOctopus(Spell* s, Character* caster, SpellTarget* target)
{
	// TODO
	// create the visual effect based on the spell name
	return new FireBallOctopus(s, caster, target);
	return nullptr;
}

