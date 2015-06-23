#pragma once
#include "OctopusBaby.h"
#include "GridOctopus.h"
#include "Spell.h"
#include "SpellTarget.h"
#include "Character.h"
#include "Panel.h"

using namespace std;

class SFOctopus :
	public OctopusBaby
{
public:
	SFOctopus(Panel* container, GridOctopus * gridO, Spell* s, Character* caster, SpellTarget* target);
	virtual ~SFOctopus();

	virtual void update();

	void setDirty(bool d = true) { _dirty = d; }
	bool isDirty() { return _dirty; }
protected:
	virtual void internalRender(SDL_Renderer* r, bool force = false);

private:
	bool _dirty = true;
	GridOctopus * _grid;
	Character* _caster;
	SpellTarget* _target;
	double ratio = 0;

	const Uint32 totalTime = 2000;
	Uint32 beginTime;
	Uint32 finishTime;

	Texture _tex;
};
