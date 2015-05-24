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
		else if (real_cell != destination_cell && _land_time + move_delay < TIMESERVICE->time())
		{
			//LOGINFO << "Moving" << endl;

			// delta time in milliseconds
			Uint32 dt = (TIMESERVICE->time() - movement_begin);

			Point origin_pos = toContainerCoordinates(_grid->toAbsoluteCoordinates(_grid->getCellCenter(real_cell)));
			Point dest_pos = toContainerCoordinates(_grid->toAbsoluteCoordinates(_grid->getCellCenter(destination_cell)));
			Point delta = abs(origin_pos - dest_pos);
			Point middle = (origin_pos - dest_pos) / 2;

			Point step = ((dest_pos - origin_pos) * dt)/move_time;

			// jump
			Point jump(0, sqrt(pow(jump_height, 2) - (pow(jump_height,2) * abs(delta.y - step.y))/pow( delta.y, 2)));

			Point pos = origin_pos + step - jump;
			Point newPos = pos + PADDING;


			step = abs(step);
			if (step.x >= delta.x && step.y >= delta.y)
			{
				//LOGINFO << "Landing on new cell" << endl;
				newPos = dest_pos + PADDING;
				real_cell = destination_cell;

				moving = false;

				_grid->unmark(destination_cell->getNumber());
				pathNext();
			}

			setPosition(newPos);
		}

		// update z-index
		setZIndex(real_cell->getNumber());

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
			SDL_RenderCopyEx(r, _basic_player, nullptr, &dst, 0.0, nullptr, (SDL_RendererFlip)orientation);

		}
	}
}

void PlayerOctopus::addMove(Cell* c)
{
	if (path.empty() || c->adjacent(path.back()))
	{
		path.push_back(c);
		_grid->mark(c->getNumber(), Color(127,127,127,50));
	//	_character->displayBasic(LOGINFO);
	//	LOGINFO << " Adding move !" << endl;
		pathNext();
	}
}
void PlayerOctopus::pathNext()
{
	if (!moving && !path.empty())
	{
		// set the next destination
		destination_cell = path.front();


		// orientation
		if (destination_cell->getPosX() > real_cell->getPosX() || (destination_cell->getPosX() == real_cell->getPosX() && destination_cell->getPosY() < real_cell->getPosY()))
		{
			orientation = RIGHT;
		}
		else
			orientation = LEFT;

		path.pop_front();
		moving = true;
		movement_begin = TIMESERVICE->time() + move_delay;
		_land_time = TIMESERVICE->time();
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