#include "PlayerOctopus.h"
#include "ServiceLocator.h"

Texture PlayerOctopus::_basic_player;
double PlayerOctopus::_ratio;
Point PlayerOctopus::PADDING;


PlayerOctopus::PlayerOctopus(Character* c, GridOctopus* grid)
	: OctopusBaby(PLAYER_WIDTH, PLAYER_HEIGHT), _character(c), _grid(grid), destination_cell(_character->getCell())
{
	if (!_basic_player.valid())
	{
		_basic_player = (*ServiceLocator::getTextureManager())["knight"];

		// compute ratio
		double ratiox = (double)_relative_rect.w / _basic_player.getWidth();
		double ratioy = (double)_relative_rect.h / _basic_player.getHeight();
		_ratio = min(ratioy, ratiox);

		// calculate padding
		PADDING = Point(-_basic_player.getWidth() * _ratio / 2, -_basic_player.getHeight() * _ratio + 7);

	}
	setBgColor(Color::TRANSPARENT);

	// event registration
	EventService* evs = EVENTSERVICE;
	evs->listen(typeid(MoveEvent), [=](Event* e) {
		MoveEvent* ev = dynamic_cast<MoveEvent*>(e);	
		if (ev && ev->getCharacter() == _character)
			addMove(ev->destination);
		}
		);
}


PlayerOctopus::~PlayerOctopus()
{
}


void PlayerOctopus::update()
{
	if (isActive() && _character)
	{
		// update position based on cell

		//LOGINFO << "Position: " << getPosition() << endl;
		if (!real_cell)
			teleport(real_cell = _character->getCell());
		else if (real_cell != destination_cell)
		{
			//LOGINFO << "Moving" << endl;

			// delta time in milliseconds
			Uint32 dt = (TIMESERVICE->time() - movement_begin);

			Point origin_pos = toContainerCoordinates(_grid->toAbsoluteCoordinates(_grid->getCellCenter(real_cell)));
			Point dest_pos = toContainerCoordinates(_grid->toAbsoluteCoordinates(_grid->getCellCenter(destination_cell)));
			Point delta = abs(origin_pos - dest_pos);

			Point step = ((dest_pos - origin_pos) * dt)/move_time;
			
			Point pos = origin_pos + step;
			Point newPos = pos + PADDING;


			step = abs(step);
			if (step.x >= delta.x && step.y >= delta.y)
			{
				//LOGINFO << "Landing on new cell" << endl;
				newPos = dest_pos + PADDING;
				real_cell = destination_cell;

				moving = false;

				pathNext();
			}

			setPosition(newPos);
		}

	}
}
void PlayerOctopus::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force || isDirty());
		if (d)
		{
			SDL_Rect dst = _relative_rect;
			dst.w = int(_ratio * _basic_player.getWidth());
			dst.h = int(_ratio * _basic_player.getHeight());
			dst.x = 0;
			dst.y = 0;
			_basic_player.render(r, nullptr, &dst);


		}
	}
}

void PlayerOctopus::addMove(Cell* c)
{
	if (path.empty() || c->adjacent(path.back()))
	{
		path.push_back(c);
		_character->displayBasic(LOGINFO);
	//	LOGINFO << " Adding move !" << endl;
		pathNext();
	}
}
void PlayerOctopus::pathNext()
{
	if (!moving && !path.empty())
	{

		destination_cell = path.front();



		// TODO: jump

		// TODO: orientation

		path.pop_front();
		moving = true;
		movement_begin = TIMESERVICE->time();
	}
}
void PlayerOctopus::teleport(const Cell* c)
{
	if (c)
	{
		Point cellCenter = toContainerCoordinates(_grid->toAbsoluteCoordinates(_grid->getCellCenter(c)));

		Point pos = cellCenter + PADDING;
		if ((Point)pos != getPosition())
		{
			setPosition(int(pos.x), int(pos.y));
		}
	}
}
void PlayerOctopus::setPosition(Point pos)
{
	if (pos != getPosition())
	{
		OctopusBaby::setPosition((int)pos.x, (int)pos.y);
	}
}