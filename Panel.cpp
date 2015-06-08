#include "Panel.h"
#include "Game.h"
#include "ServiceLocator.h"

Panel::Panel()
{
	setBgColor(Color::TRANSPARENT);
}
Panel::Panel( int w, int h)
	: OctopusBaby(w, h )
{
	setBgColor(Color::TRANSPARENT);
}



Panel::~Panel()
{
}

void Panel::update()
{
	MyList::update();
	for (auto e : _list)
	{
		e->update();
	}
}
void Panel::setActive(bool d, void*)
{
	for (auto e : _list)
	{
		e->setActive(d);
	}
	Activable::setActive(d);
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
void Panel::updateAbsoluteRect()
{
	OctopusBaby::updateAbsoluteRect();
	for (auto e : _list)
	{
		e->setContainerRect(_absolute_rect, e->getPosition());
	}
}