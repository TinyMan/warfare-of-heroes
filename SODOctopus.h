#pragma once
#include "OctopusBaby.h"
#include "PlayerOctopus.h"
#include "GridOctopus.h"
#include "Spell.h"
#include "SpellTarget.h"
#include "Panel.h"

class SODOctopus :
	public OctopusBaby
{
public:
	SODOctopus(Panel* container, GridOctopus* gridO, Spell* s, SpellTarget* target);
	virtual ~SODOctopus();

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

	const Uint32 bootstrapTime = 3000;
	const Uint32 totalTime = 3300;
	Uint32 beginTime;
	Uint32 finishTime;

	Point ori_pos, dst_pos;

	Spell* _spell;
	int width, height;

};

