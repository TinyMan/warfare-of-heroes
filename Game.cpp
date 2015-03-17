#include "Game.h"


Game::Game()
{
	ServiceLocator::provide(new EventService());
	ServiceLocator::provide(new LogService("log.txt", true));
	ServiceLocator::provide(new TimeService());
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
}

void Game::addGameObject(GameObject* g)
{
	ServiceLocator::getLogService()->write(LogService::INFO, "Adding new game object to collection");

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