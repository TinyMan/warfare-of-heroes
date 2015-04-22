#include "Panel.h"
#include "Game.h"
#include "ServiceLocator.h"

Panel::Panel()
{
}
Panel::Panel(SDL_Rect rect)
	: OctopusBaby(rect)
{
}
Panel::Panel(int x, int y, int w, int h)
	: OctopusBaby(x, y, w, h )
{
}



Panel::~Panel()
{
}

void Panel::update()
{
	MyList::update();
	
}
void Panel::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool dirty = isDirty();
		bool d = (force || dirty);
		if (d)
		{
			//LOGINFO << "rendering dirty panel" << endl;

			// draw the contained octopus babies onto the texture 
			for (auto e : _list)
			{
				//LOGINFO << "Rendering a baby in the panel " << endl;
				e->render(r, d);
			}
		}
	}
}