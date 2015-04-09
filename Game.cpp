#include "Game.h"
#include "SDLEvents.h"

Game* Game::_instance = nullptr;

Game::Game()
{
	/* instanciate services */
	_eventService = new EventService();
	_logService = new LogService("log.txt", true);
	_timeService = new TimeService();
	_userInterface = new UserInterface();
	/* and provide them */
	ServiceLocator::provide(_eventService);
	ServiceLocator::provide(_logService);
	ServiceLocator::provide(_timeService);
	ServiceLocator::provide(_userInterface);

	/* setup event listenenrs */
	_eventService->listen(typeid(Events::GameObjectEvents::ActivateEvent), EventCallback(&Game::onActivatedGameObject, this));
	_eventService->listen(typeid(Events::GameObjectEvents::DeactivateEvent), EventCallback(&Game::onDeactivatedGameObject, this));
	_eventService->listen(typeid(Events::CharacterEvents::DieEvent), EventCallback(&Game::onDie, this));
	
	/* generate basic game objects */
	_grid = new Grid();
	_octopus = new Octopus();

	initialize();
}

void Game::initialize()
{
	_octopus->initialize();
}
Game::~Game()
{
	/* destroy all last game objects */
	while (!_gameObjects.empty())
	{
		delete _gameObjects.front();
		_gameObjects.pop_front();
	}

	ServiceLocator::cleanup();
}

void Game::loop()
{
	SDL_Event e;
	Event* ev;
	cout << "Main loop !" << endl;
	while (_running)
	{
		/* TODO: BEGIN FRAME */
		_timeService->beginFrame();
		/* TODO: PROCESS USER INPUT */
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
			{
				//Quit the program
				stop();
			}
			ev = SDLEvents::createEventFromSDLEvent(&e);
		}
		//SDL_Delay(1);

		/* Update */
		_timeService->update();
		/* TODO: UPDATE */
		this->update();

		/*

		cout << "Number of active game objects: " << getNbActiveGObjects() << endl;
		*/

		/* TODO: RENDER */
		_octopus->render();
		/* TODO: END FRAME */
		_timeService->endFrame();
	}
}

void Game::addGameObject(GameObject* g)
{
	ServiceLocator::getLogService()->info << "Adding new game object to collection" << endl;
	/* we do not want null ptr in the list */
	if (g == nullptr)
		return;
	/* if it is active add it to te front */
	if (g->isActive())
	{
		_nb_active_gobjects++;
		_gameObjects.push_front(g);
	}
	else /* else add it to the back */
		_gameObjects.push_back(g);
}

void Game::addPlayer(Character* c)
{
	_players.push_back(c);
}
void Game::onDeactivatedGameObject(Event*)
{
	ServiceLocator::getLogService()->info << "Catching ev: game object deactivated" << endl;
	_gameObjects_dirty = true;
	if (_nb_active_gobjects > 0) /* prevent silly errors */
		_nb_active_gobjects--;
}
void Game::onActivatedGameObject(Event*)
{
	ServiceLocator::getLogService()->info << "Catching ev: game object activated" << endl;
	_gameObjects_dirty = true;
	_nb_active_gobjects++;
}
void Game::onDie(Event* data)
{
	if (data == nullptr)
		return;
	char a;
	Character* c = (Character*)((DieEvent*)data)->getCharacter();
	LOGINFO << c->getName() << " died !" << endl;	
	LOGINFO << "Do you want to replay (y/n) ?" << endl;
	cin >> a;
	switch (a)
	{
	case 'y':
		// TODO: reset game 
		break;
	default:
		stop();
		break;
	}
}
void Game::displayState(ostream& o) const
{
	stringstream sstm;
	o << "Currently " << _gameObjects.size() << " game objects in the list." << endl;

	/*for (auto& e : _gameObjects)
	{
		o << *e << endl;
	}*/
	displayPlayers(o);
	o << "Grid: " << endl;
	_grid->display(o);
}
void Game::displayPlayers(ostream& o) const
{
	o << "Players: " << endl;
	for (auto& e : _players)
	{
		o << *e;
		o << "<--------------------------------->" << endl;
	}
	
}
void Game::displayPlayersList(ostream& o) const
{
	int i = 0;
	o << "Players list: " << endl;
	for (auto& e : _players)
	{
		o << i++ << ": " << e->getName() << endl;
	}
}

void Game::update()
{
	/* sorting the list of game objects */
	if (_gameObjects_dirty)
	{
		_logService->info << "Game Objects list is dirty !" << endl;
		_gameObjects.sort(compare);
		_gameObjects_dirty = false;
	}
}

void Game::handleUserInput()
{
	// TODO : add textmode gameplay
	int choice = 0;
	LOGINFO << "------------------------" << endl;
	LOGINFO << "Turn " << _turn << ", player " << _player_turn << " (" << _players.at(_player_turn)->getName() << "): " << endl;
	LOGINFO << *UI << endl;


	cin >> choice;
	UI->handleChoice(choice);
}
void Game::start()
{
	beginTurn();
}
void Game::beginTurn()
{
	LOGINFO << "Begining turn of " << _players.at(_player_turn)->getName() << endl;
	UI->addAction(Action(Callback(&Game::stop, this), "Quit"));
	UI->addAction(Action(Callback(&Game::endTurn, this), "I'm done"));
	_players.at(_player_turn)->beginTurn();
	_grid->beginTurn();
}
void Game::endTurn(void* )
{
	_players.at(_player_turn)->endTurn();
	_turn += _player_turn;
	_player_turn = _player_turn == 0 ? 1 : 0;
	UI->clear();
	beginTurn();
}