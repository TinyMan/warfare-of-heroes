#include "Game.h"


Game::Game()
{
	_eventService = new EventService();
	_logService = new LogService("log.txt", true);
	_timeService = new TimeService();
	ServiceLocator::provide(_eventService);
	ServiceLocator::provide(_logService);
	ServiceLocator::provide(_timeService);

	_eventService->listen(Event::GAMEOBJECT_ACTIVATE, Callback(&Game::onToggleActivatedGameObject, this));
	_eventService->listen(Event::GAMEOBJECT_DEACTIVATE, Callback(&Game::onToggleActivatedGameObject, this));
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
	while (true)
	{
		SDL_Delay(100);
		_timeService->update();
		/*
		if (_gameObjects_dirty)
			_logService->write(INFO, "Game Objects list is dirty !");

		cout << "Number of active game objects: " << getNbActiveGObjects() << endl;
		*/
	}
}

void Game::addGameObject(GameObject* g)
{
	ServiceLocator::getLogService()->write(INFO, "Adding new game object to collection");

	if (g == nullptr)
		return;
	if (g->isActive())
	{
		_nb_active_gobjects++;
		_gameObjects.push_front(g);
	}
	else
		_gameObjects.push_back(g);
}

void Game::onToggleActivatedGameObject()
{
	_logService->write(INFO, "Catching ev: game object activated or deactivated" );
	_gameObjects_dirty = true;
	if(_nb_active_gobjects > 0) _nb_active_gobjects--;
}
void Game::displayState() const
{
	stringstream sstm;
	sstm << "Currently " << _gameObjects.size() << " game objects in the list." << endl;
	_logService->write(INFO, sstm.str());

	for (auto e : _gameObjects)
	{
		sstm << *e << endl;
		_logService->write(INFO, sstm.str());
	}
}