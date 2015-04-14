#pragma once
#include <SDL2/SDL.h>
#include "Modifiable.h"
#include "ActivableObject.h"
/* 
everything that is displayed shoudl be an octopus baby (button, player, ...)
*/
class OctopusBaby
	: public ActivableObject, public Modifiable
{
public:
	OctopusBaby();
	virtual ~OctopusBaby();

	virtual void update() = 0;
	virtual void render(SDL_Renderer* ) = 0;

	bool isAbove(const OctopusBaby& ob) { return _z_index < ob._z_index; }
private:
	int _z_index = 0;
};

