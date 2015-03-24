#include "Game.h"

Game* Game::_instance = nullptr;

Game::Game()
{
	/* instanciate services */
	_eventService = new EventService();
	_logService = new LogService("log.txt", true);
	_timeService = new TimeService();
	/* and provide them */
	ServiceLocator::provide(_eventService);
	ServiceLocator::provide(_logService);
	ServiceLocator::provide(_timeService);

	/* setup event listenenrs */
	_eventService->listen(Event::GAMEOBJECT_ACTIVATE, Callback(&Game::onActivatedGameObject, this));
	_eventService->listen(Event::GAMEOBJECT_DEACTIVATE, Callback(&Game::onDeactivatedGameObject, this));
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
	cout << "Main loop !" << endl;
	while (_running)
	{
		/* TODO: BEGIN FRAME */
		/* TODO: PROCESS USER INPUT */

		SDL_Delay(100);

		/* Update */
		_timeService->update();
		/* TODO: UPDATE */
		this->update();

		/*

		cout << "Number of active game objects: " << getNbActiveGObjects() << endl;
		*/

		/* TODO: RENDER */
		/* TODO: END FRAME */
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

void Game::onDeactivatedGameObject(void*)
{
	ServiceLocator::getLogService()->info << "Catching ev: game object deactivated" << endl;
	_gameObjects_dirty = true;
	if (_nb_active_gobjects > 0) /* prevent silly errors */
		_nb_active_gobjects--;
}
void Game::onActivatedGameObject(void*)
{
	ServiceLocator::getLogService()->info << "Catching ev: game object activated" << endl;
	_gameObjects_dirty = true;
	_nb_active_gobjects++;
}
void Game::displayState() const
{
	stringstream sstm;
	sstm << "Currently " << _gameObjects.size() << " game objects in the list." << endl;

	for (auto e : _gameObjects)
	{
		sstm << *e << endl;
	}
	_logService->info << sstm.str();
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
	cout << "Turn " << _turn << ", player " << _player_turn << ": " << endl;
	cout << "Do you want to: " << endl;
	cout << "1. Quit" << endl;
	cin >> choice;
	switch (choice)
	{
	case 1:
		stop();
		break;
	default:
		break;
	}
}