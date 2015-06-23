#pragma once
#include "Character.h"
#include "OctopusBaby.h"
#include "GridOctopus.h"
#include "Spell.h"

#include "SpellTarget.h"
#include "Panel.h"
#include "PlayerOctopus.h"

const int SPELL_WIDTH = 100;
const int SPELL_HEIGHT = 40;

class FireBallOctopus :
	public OctopusBaby{
public:
	enum ORIENTATION
	{
		LEFT = SDL_FLIP_NONE,
		RIGHT = SDL_FLIP_HORIZONTAL
	};
	//typedef SDL_RendererFlip ORIENTATION;

	//FireBallOctopus(Spell* s, Character* caster, SpellTarget* ennemi);
	FireBallOctopus(Panel* container, GridOctopus* gridO, Spell* s, SpellTarget* target);
	virtual ~FireBallOctopus();

	virtual void update();
	void setDirty(bool d = true) { _dirty = d; }
	bool isDirty() { return _dirty; }

	virtual void setPosition(int x, int y) override { OctopusBaby::setPosition(x, y); }
	virtual void setPosition(Point pos);

	void changeDestination(int x, int y); //dis quel ennemi il faut viser

protected:
	virtual void internalRender(SDL_Renderer* r, bool force = false);

private:
	bool _dirty = true;
	GridOctopus* _grid;
	ORIENTATION orientation;

	int height;
	int width;
	double ratio;

	const Cell* destination_cell;
	const Cell* origin_cell;
	const Cell* real_cell;
	bool move_wanted = true;
	Uint32 _land_time = 0;


	static Texture _basic_player;
	static double _ratio;
	static Point PADDING;

	deque<Cell*> path;
	deque<bool> move_anims;
	Uint32 movement_begin;
	bool moving = false;
	void pathNext();
	void teleport(const Cell* c);

	//Truc vraiment utile
	Point ori_pos;
	Point dst_pos;
	SpellTarget* _target;
	SpellTarget* _ennemi;
	Character* _caster;
	Spell* _spell;
	Uint32 finAnimation;
	Uint32 tempsAnimation;
	Uint32 beginTime;
	Uint32 finishTime;
	Uint32 totalTime = 2000;
	Uint32 bootstrapTime = 20;

	//Truc Utile
	double avancementX;
	double avancementY;
	double directionX;
	double directionY;
	double largeur;
	double hauteur;
};