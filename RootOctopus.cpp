#include "RootOctopus.h"



RootOctopus::RootOctopus(Panel* container, GridOctopus* gridO, Spell* s, SpellTarget* target)
	: OctopusBaby(int(gridO->getCellDimensions().x), int(gridO->getCellDimensions().y)), _grid(gridO), _spell(s), _target(target)
{
	Texture t = (*ServiceLocator::getTextureManager())["Root"];
	Point d = gridO->getCellDimensions();
	// compute ratio
	double ratiox = (double)d.x / t.getWidth();
	double ratioy = (double)d.y / t.getHeight();
	ratio = min(ratioy, ratiox);

	unsigned int n = target->getCell()->getNumber();
	Point cellCenter = gridO->getCellCenter(n);

	width = int(t.getWidth() * ratio);
	height = int(t.getHeight() * ratio);

	container->add(this);
	Point pos = toContainerCoordinates(gridO->toAbsoluteCoordinates(Point(cellCenter.x - width / 2, cellCenter.y - height/2)));

	setPositionX((int)pos.x);
	setPositionY((int)pos.y);

	setBgColor(Color::TRANSPARENT);
	setActive(true);
	setZIndex(gridO->getZIndexFromCell(n) + 1);
}


RootOctopus::~RootOctopus()
{
}


void RootOctopus::update()
{
	if (isActive())
	{
		if (!_target->hasEffect("Root Effect"))
		{
			setActive(false);
		}
	}
}


void RootOctopus::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force || isDirty());
		if (d)
		{
			Texture t = (*ServiceLocator::getTextureManager())["Root"];
			SDL_Rect dst = { 0,0, width, height };

			SDL_RenderCopy(r, t, nullptr, &dst);
		}
	}
}