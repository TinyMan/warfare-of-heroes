#include "ThunderOctopus.h"

ThunderOctopus::ThunderOctopus(Panel* container, GridOctopus* gridO, Spell* s, SpellTarget* target)
	: OctopusBaby(int(gridO->getCellDimensions().x*2), int(gridO->getCellDimensions().y * 3)), _grid(gridO), _spell(s), _target(target)
{
	Texture t = (*ServiceLocator::getTextureManager())["ThunderFrame1"];
	Point d = gridO->getCellDimensions() * 2;
	// compute ratio
	double ratiox = (double)d.x / t.getWidth();
	double ratioy = (double)d.y / t.getHeight();
	ratio = min(ratioy, ratiox);

	unsigned int n = target->getCell()->getNumber();
	Point cellCenter = gridO->getCellCenter(n);

	width = int(t.getWidth() * ratio);
	height = int(t.getHeight() * ratio);

	container->add(this);
	Point pos = toContainerCoordinates(gridO->toAbsoluteCoordinates(Point(cellCenter.x - width / 2, cellCenter.y - height - d.y)));

	setPositionX((int)pos.x);
	setPositionY((int)pos.y);


	setBgColor(Color::TRANSPARENT);
	setActive(true);
	beginTime = TIMESERVICE->time();
	finishTime = beginTime + totalTime;

	setZIndex(gridO->getZIndexFromCell(n) + 1);
}


ThunderOctopus::~ThunderOctopus()
{
}


void ThunderOctopus::update()
{
	if (isActive())
	{
		Uint32 now = TIMESERVICE->time();
		if (now > finishTime)
			setActive(false);
		else 
		{
			string name = "ThunderFrame";
			int nbFrame = 14;
			Uint32 timePerFrame = totalTime / nbFrame;

			Uint32 now = TIMESERVICE->getFrameTime();
			Uint32 elapsed = now - beginTime;

			int n = (elapsed / timePerFrame) % 14 +1;

			if (n > 7)
				n = 14 - n +1;

			setIfDifferent(_tex, (*ServiceLocator::getTextureManager())[name+to_string(n)]);
		}
	}
}


void ThunderOctopus::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force || isDirty());
		if (d)
		{
			SDL_RenderCopy(r, _tex, nullptr, nullptr);
		}
	}
}