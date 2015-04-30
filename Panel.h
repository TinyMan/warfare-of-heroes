#pragma once
#include "OctopusBaby.h"
#include "MyList.h"
#include "Texture.h"
class Panel :
	public OctopusBaby, public MyList<OctopusBaby*>
{
public:
	Panel();
	Panel(int w, int h);
	virtual ~Panel();

	virtual void update();	

	virtual bool isDirty() { return MyList::isDirty(); }
	virtual void setDirty(bool b = true) { MyList::setDirty(b); }
	virtual void add(OctopusBaby* b, Uint8 alignment = Alignment::LEFT | Alignment::TOP) { MyList::add(b); b->setContainerRect(_absolute_rect, alignment); }
	virtual void add(OctopusBaby* b, int x, int y) { MyList::add(b);  b->setContainerRect(_absolute_rect, x, y); }
	virtual void setActive(bool d = true, void* = nullptr);
protected:
	virtual void internalRender(SDL_Renderer* r, bool force = false);
	virtual void updateAbsoluteRect();
private:
};

