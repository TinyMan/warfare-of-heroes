#include "VisualEffectManager.h"
#include "Spell.h"
#include "FireBallOctopus.h"
#include "EruptionOctopus.h"
#include "SODOctopus.h"
#include "RootOctopus.h"
#include "ThunderOctopus.h"
#include "SFOctopus.h"
#include "VolleyOctopus.h"


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

		if(so)
		_effectContainer->add(so);
	}
}

OctopusBaby* VisualEffectManager::createSpellOctopus(Spell* s, Character* caster, SpellTarget* target)
{
	// TODO
	// create the visual effect based on the spell name
	if (s->getName() == "Fireball of the Doom")
		return new FireBallOctopus(_effectContainer, _gridOctopus, s, target);
	else if (s->getName() == "Eruption")
		return new EruptionOctopus(_effectContainer, _gridOctopus, s, target);
	else if (s->getName() == "Sword of Destiny")
		return new SODOctopus(_effectContainer, _gridOctopus, s, target);
	else if (s->getName() == "Root")
		return new RootOctopus(_effectContainer, _gridOctopus, s, target); 
	else if (s->getName() == "Thunder Storm")
		return new ThunderOctopus(_effectContainer, _gridOctopus, s, target);
	else if (s->getName() == "Sword Forward")
		return new SFOctopus(_effectContainer, _gridOctopus, s, caster, target);
	else if (s->getName() == "Arrow Volley")
		return new VolleyOctopus(_effectContainer, _gridOctopus, s, caster, target);
	return nullptr;
}

