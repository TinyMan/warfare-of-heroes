#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include <sstream>

#include "GameObject.h"
#include "ServiceLocator.h"

using namespace std;

/*
Main class of the game
CTOR():

*/
class Game
{
public:
	Game();
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
	void onActivatedGameObject();
	void onDeactivatedGameObject();

	/* display the current state of the game */
	void displayState() const;

	/* ending game */
	void stop() { _running = false; }
	bool isRunning() const { return _running; }
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


	/* update its state, delete objects marked etc ... */
	void update();

public:
	/* only for text mode ? */
	void handleUserInput();

};

