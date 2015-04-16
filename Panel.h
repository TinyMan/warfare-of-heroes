#pragma once
#include "OctopusBaby.h"
#include "MyList.h"
#include "Texture.h"
class Panel :
	public OctopusBaby, public MyList<OctopusBaby*>
{
public:
	Panel();
	Panel(SDL_Rect rect);
	Panel(int x, int y, int w, int h);
	virtual ~Panel();

	virtual void render(SDL_Renderer*, bool dirty = false);
	virtual void update();	

	virtual bool isDirty() { return MyList::isDirty(); }
	virtual void setDirty(bool b = true) { MyList::setDirty(b); }

	void setBackground(Texture bg) { _background = bg; }
	SDL_Texture* getBackground() const { return _background; }
private:
	SDL_Rect _rect;
	Texture _texture;
	Texture _background;

	void initialize();
};

