#include "SODOctopus.h"


SODOctopus::SODOctopus(Panel* container, GridOctopus* gridO, Spell* s, SpellTarget* target)
	: OctopusBaby(int(gridO->getCellDimensions().x*1.5), int(gridO->getCellDimensions().y*5)), _grid(gridO), _spell(s), _target(target)
{	
	Texture t = (*ServiceLocator::getTextureManager())["SwordDestiny"];
	Point d = gridO->getCellDimensions() * 3;
	// compute ratio
	double ratiox = (double)d.x / t.getWidth();
	double ratioy = (double)d.y / t.getHeight();
	ratio = min(ratioy, ratiox);

	unsigned int n = target->getCell()->getNumber();
	Point cellCenter = gridO->getCellCenter(n);
	
	width = int(t.getWidth() * ratio);
	height = int(t.getHeight() * ratio);

	container->add(this);
	Point pos = toContainerCoordinates(gridO->toAbsoluteCoordinates(Point(cellCenter.x - width / 2, cellCenter.y - height - d.y/3)));

	ori_pos = pos;
	dst_pos = toContainerCoordinates(gridO->toAbsoluteCoordinates(Point(cellCenter.x - width / 2, cellCenter.y - height)));

	setPositionX((int)pos.x);
	setPositionY((int)pos.y);

	setBgColor(Color::TRANSPARENT);
	setActive(true);
	beginTime = TIMESERVICE->time();
	finishTime = beginTime + totalTime;

	setZIndex(gridO->getZIndexFromCell(n) + 1);
}


SODOctopus::~SODOctopus()
{
}


void SODOctopus::update()
{
	if (isActive() )
	{
		Uint32 now = TIMESERVICE->time();
		if (now > finishTime)
			setActive(false);
		else if (now > beginTime + bootstrapTime)
		{
			Uint32 dt = now - (beginTime + bootstrapTime);
			Point delta = dst_pos - ori_pos;

			Point step = (delta * dt) / (totalTime- bootstrapTime);
			Point newPos = ori_pos + step;
			setPositionX((int)newPos.x);
			setPositionY((int)newPos.y);
		}
	}
}


void SODOctopus::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force || isDirty());
		if (d)
		{
			Texture t = (*ServiceLocator::getTextureManager())["SwordDestiny"];
			SDL_Rect dst = { 0, 0, width, height };
			SDL_RenderCopy(r, t, nullptr, &dst);
		}
	}
}