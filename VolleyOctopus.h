#pragma once
#include "OctopusBaby.h"
#include "GridOctopus.h"
#include "Spell.h"
#include "SpellTarget.h"
#include "Character.h"
#include "Panel.h"

using namespace std;

class VolleyOctopus :
	public OctopusBaby
{
public:
	VolleyOctopus(Panel* container, GridOctopus * gridO, Spell* s, Character* caster, SpellTarget* target);
	virtual ~VolleyOctopus();

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
	Texture _tex;

	const Uint32 bootstrapTime = 400;
	const Uint32 animTime = 600;
	const Uint32 totalTime = animTime + bootstrapTime;
	Uint32 beginTime;
	Uint32 finishTime;


};

