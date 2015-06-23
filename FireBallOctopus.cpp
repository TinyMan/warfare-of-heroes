#include "FireBallOctopus.h"


FireBallOctopus::FireBallOctopus(Panel* container, GridOctopus* gridO, Spell* s, Character* caster, SpellTarget* target)
	: OctopusBaby(int(gridO->getCellDimensions().x*3), int(gridO->getCellDimensions().y * 3)), _grid(gridO), _spell(s), _caster(caster), _target(target)
{
	Texture t = (*ServiceLocator::getTextureManager())["FireBallFrame1"];
	Point d = gridO->getCellDimensions() * 1.5;
	// compute ratio
	double ratiox = (double)d.x / t.getWidth();
	double ratioy = (double)d.y / t.getHeight();
	ratio = min(ratioy, ratiox);

	unsigned int n = target->getCell()->getNumber();
	Point cellCenter = gridO->getCellCenter(n);
	//pour le caster en dessous
	n = caster->getCell()->getNumber();
	Point departCenter = gridO->getCellCenter(n);

	width = int(t.getWidth() * ratio);
	height = int(t.getHeight() * ratio);

	container->add(this);
	Point pos = toContainerCoordinates(gridO->toAbsoluteCoordinates(Point(departCenter.x - width / 2, departCenter.y - height)));
	//Point pos = toContainerCoordinates(gridO->toAbsoluteCoordinates(Point(departCenter.x - width / 2, departCenter.y - height - d.y / 3)));

	ori_pos = pos;
	dst_pos = toContainerCoordinates(gridO->toAbsoluteCoordinates(Point(cellCenter.x - width / 2, cellCenter.y - height)));

	setPositionX((int)pos.x);
	setPositionY((int)pos.y);

	setBgColor(Color::TRANSPARENT);
	setActive(true);
	beginTime = TIMESERVICE->time();
	finishTime = beginTime + totalTime;

	setZIndex(gridO->getZIndexFromCell(Grid::CELLS_NUMBER-1) + 1);

	//orientation
	if (ori_pos.x>dst_pos.x)
	{
		orientation = RIGHT;
	}
	else
		orientation = LEFT;

}


FireBallOctopus::~FireBallOctopus()
{
}


void FireBallOctopus::update()
{
	if (isActive())
	{
		Uint32 now = TIMESERVICE->time();
		if (now > finishTime)
			setActive(false);
		else if (now > beginTime)
		{

			string name = "FireBallFrame";
			int nbFrame = 4;
			Uint32 timePerFrame = 50;

			Uint32 now = TIMESERVICE->getFrameTime();
			Uint32 elapsed = now - beginTime;

			int n = (elapsed / timePerFrame) % 4 + 1;
			

			setIfDifferent(_tex, (*ServiceLocator::getTextureManager())[name + to_string(n)]);



			Uint32 dt = now - (beginTime);
			Point delta = dst_pos - ori_pos;

			Point step = (delta * dt) / (totalTime);
			Point newPos = ori_pos + step;
			setPositionX((int)newPos.x);
			setPositionY((int)newPos.y);
		}
	}
}


void FireBallOctopus::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force || isDirty());
		/*if (d)
		{
			SDL_Rect dst = { 0, 0, width, height };
			SDL_RenderCopyEx(r, _tex, nullptr, &dst, angleInclinaison, nullptr, (SDL_RendererFlip)orientation);
		}*/

		Point from = _grid->getCellCenter(_caster->getCell()->getNumber());
		Point to = _grid->getCellCenter(_target->getCell()->getNumber());

		from.x -= 15;
		to.x -= 15;

		Point delta = to - from;

		double angle = getAngleFromPoint(from, to) - 90;

		//SDL_Rect dst = { int(from.x), int(from.y), width, width };
		SDL_Rect dst = { 0, (height) / 2, width, height };

		SDL_Point center = { height/2, 0 };
		SDL_RenderCopyEx(r, _tex, nullptr, &dst, angle, nullptr, SDL_FLIP_VERTICAL);
	}
}

