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
			for (Cell* c : _target->getCells())
			{
				Point center = _grid->getCellCenter(c->getNumber());
				SDL_Rect dst = { center.x, center.y, int(t.getWidth() * ratio), int(t.getHeight() * ratio) };

				SDL_RenderCopy(r, t, nullptr, &dst);
			}
		}
	}
}