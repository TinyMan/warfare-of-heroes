#pragma once
#include <SDL2/SDL.h>
#include "Activable.h"
#include "Sortable.h"
#include "Texture.h"

/* 
everything that is displayed shoudl be an octopus baby (button, player, ...)
*/
class OctopusBaby
	: public Activable, public Sortable
{
public:
	OctopusBaby();
	OctopusBaby(SDL_Rect rect);
	OctopusBaby(int x, int y, int w, int h);
	virtual ~OctopusBaby();

	virtual void update() = 0;
	virtual void render(SDL_Renderer* , bool forceRender = false);

	bool isAbove(const OctopusBaby& ob) const { return _z_index < ob._z_index; }
	void setZIndex(int z);
	int getZIndex() const { return _z_index; }

	bool operator<(const OctopusBaby& o) const;

	virtual bool compare(const Sortable* s) const;

	void setBackground(Texture bg) { _background = bg; setDirty(); }
	SDL_Texture* getBackground() const { return _background; }
	void setContainerRect(SDL_Rect r) { _container_rect = r; updateAbsoluteRect(); }
protected:
	SDL_Rect _relative_rect;
	SDL_Rect _absolute_rect;
	SDL_Rect _container_rect;
	Texture _texture;
	Texture _background;
	virtual void internalRender(SDL_Renderer* r, bool force = false) = 0;
	void updateAbsoluteRect();
private:
	int _z_index = 0;
	void initialize();
};
