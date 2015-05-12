#pragma once
#include "OctopusBaby.h"
class PlayerOctopus :
	public OctopusBaby
{
public:
	PlayerOctopus();
	virtual ~PlayerOctopus();

	virtual void update();
	void setDirty(bool d = true) { _dirty = d; }
	bool isDirty() { return _dirty; }

protected:
	virtual void internalRender(SDL_Renderer* r, bool force = false);

private:
	bool _dirty = true;

	static Texture _basic_player;
};

