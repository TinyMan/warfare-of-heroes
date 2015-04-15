#pragma once
#include "OctopusBaby.h"
#include "MyList.h"
class Panel :
	public OctopusBaby, public MyList<OctopusBaby*>
{
public:
	Panel(SDL_Rect rect);
	Panel(int x = 0, int y = 0, int w = 0, int h = 0);
	virtual ~Panel();

	virtual void render(SDL_Renderer*, bool dirty = false);
	virtual void update();	

	virtual bool isDirty() { return MyList::isDirty(); }
	virtual void setDirty(bool b = true) { MyList::setDirty(b); }


private:
	SDL_Rect _rect;
	SDL_Texture* _texture;

	void initialize();
};

