#pragma once
#include "OctopusBaby.h"
#include "PlayerOctopus.h"
#include "GridOctopus.h"
#include "Spell.h"
#include "SpellTarget.h"
#include "Panel.h"

class ThunderOctopus :
	public OctopusBaby
{
public:
	ThunderOctopus(Panel* container, GridOctopus* gridO, Spell* s, SpellTarget* target);
	virtual ~ThunderOctopus();

	virtual void update();
	void setDirty(bool d = true) { _dirty = d; }
	bool isDirty() { return _dirty; }

protected:
	virtual void internalRender(SDL_Renderer* r, bool force = false);

private:
	bool _dirty = true;
	GridOctopus * _grid;
	SpellTarget* _target;
	double ratio = 0;


	const Uint32 totalTime = 8000;
	Uint32 beginTime;
	Uint32 finishTime;

	Texture _tex;



	Spell* _spell;
	int width, height;

};

