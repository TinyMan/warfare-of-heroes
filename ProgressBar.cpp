#include "ProgressBar.h"
#include "ServiceLocator.h"

ProgressBar::ProgressBar()
{
}

ProgressBar::ProgressBar(int x, int y)
	: OctopusBaby(x, y)
{
}


ProgressBar::~ProgressBar()
{
}

void ProgressBar::update()
{

}
void ProgressBar::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = force | isDirty();
		if (d)
		{
			//LOGINFO << "Drawing ProgressBar " << endl;
			SDL_Rect rect = { 0, 0 , _relative_rect.w, _relative_rect.h };

			rect.w = int(_value * rect.w / 100);
			_foreground_color.setRenderDrawColor(r);
			SDL_RenderFillRect(r, &rect);

			rect.w = _relative_rect.w;
			_border_color.setRenderDrawColor(r);
			SDL_RenderDrawRect(r, &rect);
		}
	}
}