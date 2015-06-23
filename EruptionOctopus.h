#pragma once
#include "OctopusBaby.h"
#include "GridOctopus.h"
#include "Spell.h"
#include "SpellTarget.h"
#include "Character.h"
#include "Panel.h"

using namespace std;

class EruptionOctopus :
	public OctopusBaby
{
public:
	EruptionOctopus(Panel* container, GridOctopus * gridO, Spell* s, SpellTarget* target);
	virtual ~EruptionOctopus();

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


};

