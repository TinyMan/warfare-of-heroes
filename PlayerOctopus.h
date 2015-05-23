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

	void addMove(Cell* c);

	void computePixelPos();

	static const Uint32 move_time = 300;
	static const Uint32 jump_height = 35;
	static const Uint32 move_delay = 200;
	virtual void setPosition(int x, int y) override { OctopusBaby::setPosition(x, y); }
	virtual void setPosition(Point pos);
	//virtual void updateAbsoluteRect() override { OctopusBaby::updateAbsoluteRect(); teleport(_character->getCell()); }
protected:
	virtual void internalRender(SDL_Renderer* r, bool force = false);

private:
	bool _dirty = true;
	Character* _character;
	GridOctopus* _grid;
	ORIENTATION orientation;

	const Cell* destination_cell;
	const Cell* origin_cell;
	const Cell* real_cell;
	Uint32 _land_time = 0;


	static Texture _basic_player;
	static double _ratio;
	static Point PADDING;

	deque<Cell*> path;
	Uint32 movement_begin;
	bool moving = false;
	void pathNext();
	void teleport(const Cell* c);
};

