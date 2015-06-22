#pragma once
#include "Character.h"
#include "OctopusBaby.h"
#include "GridOctopus.h"

const int PLAYER_WIDTH = 50;
const int PLAYER_HEIGHT = 60;

class PlayerOctopus :
	public OctopusBaby
{
public:
	enum ORIENTATION
	{
		LEFT = SDL_FLIP_NONE,
		RIGHT = SDL_FLIP_HORIZONTAL
	};
	//typedef SDL_RendererFlip ORIENTATION;

	PlayerOctopus(Character* c, GridOctopus* grid);
	virtual ~PlayerOctopus();

	virtual void update();
	void setDirty(bool d = true) { _dirty = d; }
	bool isDirty() { return _dirty; }

	void addMove(Cell* c, bool moveWanted);

	void computePixelPos();

	static const Uint32 move_time = 300;
	static const Uint32 jump_height = 5;
	static const Uint32 move_delay = 200;
	virtual void setPosition(int x, int y) override { OctopusBaby::setPosition(x, y); }
	virtual void setPosition(Point pos);

protected:
	virtual void internalRender(SDL_Renderer* r, bool force = false);
	Point getPadding() const;

private:
	bool _dirty = true;
	Character* _character;
	GridOctopus* _grid;
	ORIENTATION orientation;

	const Cell* destination_cell;
	const Cell* origin_cell;
	const Cell* real_cell;
	bool move_wanted = true;
	Uint32 _land_time = 0;


	static Texture _basic_player;
	static double _ratio;
	static Point PADDINGFaceLeft;
	static Point PADDINGFaceRight;

	deque<Cell*> path;
	deque<bool> move_anims;
	Uint32 movement_begin;
	bool moving = false;
	void pathNext();
	void teleport(const Cell* c);
};

