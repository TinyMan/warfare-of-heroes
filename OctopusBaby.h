#pragma once
#include <SDL2/SDL.h>
#include "Activable.h"
#include "Sortable.h"

/* 
everything that is displayed shoudl be an octopus baby (button, player, ...)
*/
class OctopusBaby
	: public Activable, public Sortable
{
public:
	OctopusBaby();
	virtual ~OctopusBaby();

	virtual void update() = 0;
	virtual void render(SDL_Renderer* , bool dirty = false) = 0;

	bool isAbove(const OctopusBaby& ob) const { return _z_index < ob._z_index; }
	void setZIndex(int z);
	int getZIndex() const { return _z_index; }

	bool operator<(const OctopusBaby& o) const;

	virtual bool compare(const Sortable* s) const;
private:
	int _z_index = 0;
};
