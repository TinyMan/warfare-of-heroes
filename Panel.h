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

	virtual void update();	

	virtual bool isDirty() { return MyList::isDirty(); }
	virtual void setDirty(bool b = true) { MyList::setDirty(b); }
	virtual void add(OctopusBaby* b) { MyList::add(b); b->setContainerRect(_absolute_rect); }
protected:
	virtual void internalRender(SDL_Renderer* r, bool force = false);
private:
};

