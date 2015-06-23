#include "SFOctopus.h"

SFOctopus::SFOctopus(Panel* container, GridOctopus * gridO, Spell* s, Character* caster, SpellTarget* target)
	: OctopusBaby(gridO->getRelativeRect().w, gridO->getRelativeRect().h), _grid(gridO), _target(target), _caster(caster)
{

	Texture t = (*ServiceLocator::getTextureManager())["SwordForwardFrame10"];

	Point from = _grid->getCellCenter(_caster->getCell()->getNumber());
	Point to = _grid->getCellCenter(_target->getCell()->getNumber());
	Point delta = to - from;
	double d = sqrt(delta.x  * delta.x + delta.y * delta.y);

	ratio = d / t.getHeight();


	container->add(this, gridO->getPosition().x, gridO->getPosition().y);
	setBgColor(Color::TRANSPARENT);
	setActive(true);
	beginTime = TIMESERVICE->time();
	finishTime = beginTime + totalTime;
	setZIndex(gridO->getZIndexFromCell(Grid::CELLS_NUMBER-1)+1);
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
			string name = "SwordForwardFrame";
			int nbFrame = 10;
			Uint32 timePerFrame = totalTime / nbFrame;

			Uint32 now = TIMESERVICE->getFrameTime();
			Uint32 elapsed = now - beginTime;

			int n = (elapsed / timePerFrame) % nbFrame + 1;


			setIfDifferent(_tex, (*ServiceLocator::getTextureManager())[name + to_string(n)]);
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
			Point from = _grid->getCellCenter(_caster->getCell()->getNumber());
			Point to =_grid->getCellCenter(_target->getCell()->getNumber());

			from.x -= 15;
			to.x -= 15;

			Point delta = to - from;

			double angle = getAngleFromPoint(from, to);

			SDL_Rect dst = { int(from.x), int(from.y), int(_grid->getCellDimensions().y), int(770 * ratio) };


			SDL_Point center = { 15,0 };
			SDL_RenderCopyEx(r, _tex, nullptr, &dst,angle+180, &center, SDL_FLIP_VERTICAL);
		}
	}
}