#include "VolleyOctopus.h"

VolleyOctopus::VolleyOctopus(Panel* container, GridOctopus * gridO, Spell* s, Character* caster, SpellTarget* target)
	: OctopusBaby(gridO->getRelativeRect().w, gridO->getRelativeRect().h), _grid(gridO), _target(target), _caster(caster)
{

	Texture t = (*ServiceLocator::getTextureManager())["VoleeFlechesFrame1"];
	Point d = gridO->getCellDimensions() * 5;
	// compute ratio
	double ratiox = (double)d.x / t.getWidth();
	double ratioy = (double)d.y / t.getHeight();
	ratio = min(ratioy, ratiox);


	container->add(this, gridO->getPosition().x, gridO->getPosition().y);
	setBgColor(Color::TRANSPARENT);
	setActive(false);
	beginTime = TIMESERVICE->time();
	finishTime = beginTime + totalTime;
}


VolleyOctopus::~VolleyOctopus()
{
}


void VolleyOctopus::update()
{
	Uint32 now = TIMESERVICE->time();
	if (isActive())
	{
		if (now > finishTime)
		{
			setActive(false);
		}
		else
		{
			string name = "VoleeFlechesFrame";

			int nbFrame = 10;
			Uint32 timePerFrame = animTime / nbFrame;

			Uint32 now = TIMESERVICE->getFrameTime();
			Uint32 elapsed = now - beginTime - bootstrapTime;

			int n = (elapsed / timePerFrame) % nbFrame + 1;

			setIfDifferent(_tex, (*ServiceLocator::getTextureManager())[name + to_string(n)]);
		}
	}
	else if (now > beginTime + bootstrapTime && now < finishTime)
	{
		setActive();
	}
}

void VolleyOctopus::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force || isDirty());
		if (d)
		{
			int width = int(_tex.getWidth() * ratio), height = int(_tex.getHeight() * ratio);

			//for (Cell* c : _target->getCells())
			//{
				Point center = _grid->getCellCenter(_target->getCell()->getNumber());
				SDL_Rect dst = { int(center.x - width / 2), int(center.y - height / 2), width, height };

				SDL_RenderCopy(r, _tex, nullptr, &dst);
			//}
		}
	}
}