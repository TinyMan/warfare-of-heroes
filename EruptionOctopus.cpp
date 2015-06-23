#include "EruptionOctopus.h"


EruptionOctopus::EruptionOctopus(Panel* container, GridOctopus * gridO, Spell* s, SpellTarget* target)
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
	finishTime = beginTime + bootstrapTime;
}


EruptionOctopus::~EruptionOctopus()
{
}


void EruptionOctopus::update()
{
	if (isActive())
	{
		if (!_target->getCell()->hasEffect("Eruption DoT"))
		{
			setActive(false);
		}
		else if (TIMESERVICE->time() < beginTime + bootstrapTime)
		{
			Uint32 now = TIMESERVICE->time();
			Uint32 dt = now - beginTime;
			
			setAlpha(Uint8((255 / (double)bootstrapTime) * dt));
		}
		else
		{
			setAlpha(255);
		}
	}
}

void EruptionOctopus::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force || isDirty());
		if (d)
		{
			Texture t = (*ServiceLocator::getTextureManager())["Eruption"];
			int width = int(t.getWidth() * ratio), height = int(t.getHeight() * ratio);

			for (Cell* c : _target->getCells())
			{
				Point center = _grid->getCellCenter(c->getNumber());
				SDL_Rect dst = { int(center.x - width/2), int(center.y - height/2), width, height };

				SDL_RenderCopy(r, t, nullptr, &dst);
			}
		}
	}
}