#pragma once
#include <map>
#include <string>
#include "ServiceLocator.h"
#include "SpellEvents.h"

using namespace std;
using namespace Events::SpellEvents;

class SoundEffectManager
{
public:
	SoundEffectManager();
	virtual ~SoundEffectManager();

	virtual void onCast(Event* e);

private:
	static const map<string, string> soundEffectsFilenames; /* first-> spell name, second-> filename */
	static map<string, string> mapFilenames();
};

