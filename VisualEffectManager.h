#pragma once
#include <map>
#include <string>
#include "ServiceLocator.h"
#include "SpellEvents.h"
#include "GridOctopus.h"
#include "Panel.h"

using namespace std;
using namespace Events::SpellEvents;

class SpellOctopus;

class VisualEffectManager
{
public:
	VisualEffectManager();
	virtual ~VisualEffectManager();

	virtual void onCast(Event* e);

	void setGridOctopus(GridOctopus* go) { _gridOctopus = go; }
	void setEffectContainer(Panel* ec) { _effectContainer = ec; }

protected:
	OctopusBaby* createSpellOctopus(Spell* s, Character* caster, SpellTarget* target);

private:
	Panel* _effectContainer = nullptr;
	GridOctopus* _gridOctopus = nullptr;
};
