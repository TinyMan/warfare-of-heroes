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
	OctopusBaby(int w, int h);
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

	void setBackground(const Texture& bg) { _background = bg; setDirty(); }
	Texture getBackground() const { return _background; }
	void setContainerRect(SDL_Rect r, SDL_Point p) { setContainerRect(r, p.x, p.y); }
	void setContainerRect(SDL_Rect r, int x = 0, int y = 0) { _container_rect = r; setPosition(x, y); }
	void setContainerRect(SDL_Rect r, Uint8 alignment) { _container_rect = r; setPosition(alignment); }

	void setPosition(Uint8 alignment);
	void setPosition(int x, int y);
	void setPositionX(int x);
	void setPositionY(int y);
	SDL_Rect getAbsolutRect() const{ return _absolute_rect; }
	SDL_Point getPosition() const { return { _relative_rect.x, _relative_rect.y }; }
	SDL_Point getAbsolutePosition() const { return{ _absolute_rect.x, _absolute_rect.y }; }

	// 0 is transparent and 255 is opaque
	void setAlpha(Uint8 alpha);
	Uint8 getAlpha() const;
	virtual bool isInArea(SDL_Point p) const;
protected:
	SDL_Rect _relative_rect;
	SDL_Rect _absolute_rect;
	SDL_Rect _container_rect;
	Texture _texture;
	Texture _background;
	virtual void internalRender(SDL_Renderer* r, bool force = false) = 0;
	virtual void updateAbsoluteRect();
private:
	int _z_index = 0;
	void initialize();
};
