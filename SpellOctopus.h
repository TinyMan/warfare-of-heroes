#pragma once
#include "Character.h"
#include "OctopusBaby.h"
#include "GridOctopus.h"

const int SPELL_WIDTH = 50;
const int SPELL_HEIGHT = 60;

class SpellOctopus :
	public OctopusBaby
{
public:
	enum ORIENTATION
	{
		LEFT = SDL_FLIP_NONE,
		RIGHT = SDL_FLIP_HORIZONTAL
	};
	//typedef SDL_RendererFlip ORIENTATION;

	SpellOctopus(string spell, unsigned int c,GridOctopus* grid);
	virtual ~SpellOctopus();

	virtual void update();
	void setDirty(bool d = true) { _dirty = d; }
	bool isDirty() { return _dirty; }
	
	virtual void setPosition(int x, int y) override { OctopusBaby::setPosition(x, y); }
	virtual void setPosition(Point pos);
	
	void changeDestination(int x, int y);
	void moveSpell();

protected:
	virtual void internalRender(SDL_Renderer* r, bool force = false);

private:
	bool _dirty = true;
	GridOctopus* _grid;
	ORIENTATION orientation;

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

	//Truc Utile
	 int depX;
	 int depY;
	 int destX;
	 int destY;
	 string nomduSpell;
	 double vitesseSpell;
	 double orientationSpell;
	 double avancementX;
	 double avancementY;
	 double directionX;
	 double directionY;
	 double largeur;
	 double hauteur;
};

