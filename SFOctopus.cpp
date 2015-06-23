#include "SFOctopus.h"

SFOctopus::SFOctopus(Panel* container, GridOctopus * gridO, Spell* s, SpellTarget* target)
	: OctopusBaby(gridO->getRelativeRect().w, gridO->getRelativeRect().h), _grid(gridO), _target(target)
{

	Texture t = (*ServiceLocator::getTextureManager())["Eruption"];
	Point d = gridO->getCellDimensions();
	// compute ratio
	double ratiox = (double)d.x / t.getWidth();
	double ratioy = (double)d.y / t.getHeight();
	ratio = min(ratioy, ratiox);


	container->add(this, gridO->getPosition().x, gridO->getPosition().y);
	setBgColor(Color::TRANSPARENT);
	setActive(true);
	beginTime = TIMESERVICE->time();
	finishTime = beginTime + totalTime;
}

SFOctopus::~SFOctopus()
{
}


void SFOctopus::update()
{
	if (isActive())
	{
		Uint32 now = TIMESERVICE->time();
		if (now > finishTime)
			setActive(false);
		else
		{

		}
	}
}

void SFOctopus::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force || isDirty());
		if (d)
		{
			
		}
	}
}