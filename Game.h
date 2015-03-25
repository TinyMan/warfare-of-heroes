#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include <sstream>

#include "GameObject.h"
#include "ServiceLocator.h"

using namespace std;

#define UI ServiceLocator::getUI()

/*
Main class of the game
Singleton thx

*/
class Game
{
public:
	~Game();

	void initialize();
	void loop();

	/* Add a game object to the collection */
	void addGameObject(GameObject* g);

	template<typename... GO>
	/* Add multiple game objects to the collection */
	void addGameObject(GameObject* g, GO... a){
		/* add the first */
		addGameObject(g);	
		/* recursive call if there is many, or call the fc above if there is only 1 last */
		addGameObject(a...);
	}

	int getNbActiveGObjects() const { return _nb_active_gobjects; }

	/* event listeners */
	void onActivatedGameObject(void*);
	void onDeactivatedGameObject(void*);

	/* display the current state of the game */
	void displayState() const;

	/* ending game */
	void stop(void*d=nullptr) { _running = false; }
	bool isRunning() const { return _running; }

	static Game* getInstance() { if (!_instance) _instance = new Game; return _instance; }

private:
	/* the collection of all game objects, sorted with the active ones on the front and the inactive ones after them */
	list<GameObject*> _gameObjects;
	/* number of active gameobjects */
	int _nb_active_gobjects = 0;
	/* true if we need to sort _gameObjects list */
	bool _gameObjects_dirty = false;


	bool _running = true;
	bool _turn = 0;
	int _player_turn = 0; // the current player ID which play 

	TimeService * _timeService = nullptr;
	LogService * _logService = nullptr;
	EventService* _eventService = nullptr;
	UserInterface* _userInterface = nullptr;


	/* update its state, delete objects marked etc ... */
	void update();

	/* private constructor because of singleton. Call Game::initialize() or Game::getInstance() to get the instance */
	Game();

	static Game* _instance;
public:
	/* only for text mode ? */
	void handleUserInput();

};

