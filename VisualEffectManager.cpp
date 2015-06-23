#include "VisualEffectManager.h"
#include "Spell.h"
#include "FireBallOctopus.h"
#include "FlammedArrow.h"
#include "StepBackOctopus.h"


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

		if (so)
			_effectContainer->add(so);
	}
}
/*
OctopusBaby* VisualEffectManager::createSpellOctopus(Spell* s, Character* caster, SpellTarget* target)
{
	// TODO
	// create the visual effect based on the spell name
	return new FireBallOctopus(s, caster, target);
	return nullptr;
}
*/

OctopusBaby* VisualEffectManager::createSpellOctopus(Spell* s, Character* caster, SpellTarget* target)
{
	// TODO
	// create the visual effect based on the spell name
	if (s->getName() == "Fireball of the Doom")
		return new FireBallOctopus(_effectContainer, _gridOctopus, s, caster, target);
	else if (s->getName() == "Flamed Arrow")
		return new FlammedArrow(_effectContainer, _gridOctopus, s, caster, target);
	else if (s->getName() == "Step-Back Arrow")
		return new StepBackOctopus(_effectContainer, _gridOctopus, s, caster, target);
	/*else if (s->getName() == "Eruption")
		return new EruptionOctopus(_effectContainer, _gridOctopus, s, target);
	else if (s->getName() == "Sword of Destiny")
		return new SODOctopus(_effectContainer, _gridOctopus, s, target);
	else if (s->getName() == "Root")
		return new RootOctopus(_effectContainer, _gridOctopus, s, target);*/
	return nullptr;
}
