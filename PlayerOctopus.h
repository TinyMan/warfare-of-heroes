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
	PlayerOctopus(Character* c, GridOctopus* grid);
	virtual ~PlayerOctopus();

	virtual void update();
	void setDirty(bool d = true) { _dirty = d; }
	bool isDirty() { return _dirty; }

protected:
	virtual void internalRender(SDL_Renderer* r, bool force = false);

private:
	bool _dirty = true;
	Character* _character;
	GridOctopus* _grid;

	static Texture _basic_player;
};

