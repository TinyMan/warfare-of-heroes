#include "SoundEffectManager.h"
#include "Spell.h"
const map<string, string> SoundEffectManager::soundEffectsFilenames = SoundEffectManager::mapFilenames();
map<string, string> SoundEffectManager::mapFilenames()
{
	string path = "sound/sfx/";
	map<string, string> m;
	m["Arrow Volley"] = path + "arrow_volley.wav";
	m["Step-Back Arrow"] = path + "step_back_arrow.wav";
	m["Flamed Arrow"] = path + "fire_arrow.wav";
	m["Damage Buff"] = path + "damage_buff.wav";

	m["Dash"] = path + "dash.wav";
	m["Heal"] = path + "heal.wav";
	m["Sword of Destiny"] = path + "sword_of_destiny.wav";
	m["Sword Forward"] = path + "sword_extension.wav";

	m["Root"] = path + "root.wav";
	m["Fireball of the Doom"] = path + "fireball.wav";
	m["Thunder Storm"] = path + "thunder.wav";
	m["Eruption"] = path + "eruption.wav";

	return m;
}
SoundEffectManager::SoundEffectManager()
{
	EVENTSERVICE->listen(typeid(SpellCastEvent),  EventCallback(&SoundEffectManager::onCast, this));
	for (auto c : soundEffectsFilenames)
	{
		SOUNDSERVICE->loadEffect(c.second, c.first);
	}
}


SoundEffectManager::~SoundEffectManager()
{
}

void SoundEffectManager::onCast(Event* e)
{
	SpellCastEvent *ev = dynamic_cast<SpellCastEvent*>(e);
	if (ev)
	{
		SOUNDSERVICE->playEffect(ev->spell->getName());
	}
}
