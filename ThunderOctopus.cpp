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
			Uint32 vitesse = totalTime;
			int nbFrame = 7;
			Uint32 duree = totalTime;
			if (TIMESERVICE->getFrameTime() % vitesse >= 0 && TIMESERVICE->getFrameTime() % vitesse < 100)
				setIfDifferent(_tex, (*ServiceLocator::getTextureManager())["ThunderFrame1"]);
			else if (TIMESERVICE->getFrameTime() % vitesse >= 100 && TIMESERVICE->getFrameTime() % vitesse < 200)
				setIfDifferent(_tex, (*ServiceLocator::getTextureManager())["ThunderFrame2"]);
			else if (TIMESERVICE->getFrameTime() % vitesse >= 200 && TIMESERVICE->getFrameTime() % vitesse < 300)
				setIfDifferent(_tex, (*ServiceLocator::getTextureManager())["ThunderFrame3"]);
			else if (TIMESERVICE->getFrameTime() % vitesse >= 300 && TIMESERVICE->getFrameTime() % vitesse < 400)
				setIfDifferent(_tex, (*ServiceLocator::getTextureManager())["ThunderFrame4"]);
			else if (TIMESERVICE->getFrameTime() % vitesse >= 400 && TIMESERVICE->getFrameTime() % vitesse < 2000)
				setIfDifferent(_tex, (*ServiceLocator::getTextureManager())["ThunderFrame5"]);
			else if (TIMESERVICE->getFrameTime() % vitesse >= 2000 && TIMESERVICE->getFrameTime() % vitesse < 2500)
				setIfDifferent(_tex, (*ServiceLocator::getTextureManager())["ThunderFrame6"]);
			else if (TIMESERVICE->getFrameTime() % vitesse >= 2500 && TIMESERVICE->getFrameTime() % vitesse < 4000)
				setIfDifferent(_tex, (*ServiceLocator::getTextureManager())["ThunderFrame5"]);
			else if (TIMESERVICE->getFrameTime() % vitesse >= 4000 && TIMESERVICE->getFrameTime() % vitesse < 4500)
				setIfDifferent(_tex, (*ServiceLocator::getTextureManager())["ThunderFrame7"]);
			else if (TIMESERVICE->getFrameTime() % vitesse >= 4500 && TIMESERVICE->getFrameTime() % vitesse < 7600)
				setIfDifferent(_tex, (*ServiceLocator::getTextureManager())["ThunderFrame5"]);
			else if (TIMESERVICE->getFrameTime() % vitesse >= 7600 && TIMESERVICE->getFrameTime() % vitesse < 7700)
				setIfDifferent(_tex, (*ServiceLocator::getTextureManager())["ThunderFrame4"]);
			else if (TIMESERVICE->getFrameTime() % vitesse >= 7700 && TIMESERVICE->getFrameTime() % vitesse < 7800)
				setIfDifferent(_tex, (*ServiceLocator::getTextureManager())["ThunderFrame3"]);
			else if (TIMESERVICE->getFrameTime() % vitesse >= 7800 && TIMESERVICE->getFrameTime() % vitesse < 7900)
				setIfDifferent(_tex, (*ServiceLocator::getTextureManager())["ThunderFrame2"]);
			else if (TIMESERVICE->getFrameTime() % vitesse >= 7900 && TIMESERVICE->getFrameTime() % vitesse < 7999)
				setIfDifferent(_tex, (*ServiceLocator::getTextureManager())["ThunderFrame1"]);

			//setDirty();
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