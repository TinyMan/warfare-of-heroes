#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include <deque>
#include <sstream>

#include "GameObject.h"
#include "Character.h"
#include "Grid.h"
#include "ServiceLocator.h"
#include "CharacterEvents.h"

#define GAMEINST Game::getInstance()

using namespace std;
using namespace Events;
using namespace Events::CharacterEvents;


/*
Main class of the game
Singleton thx

*/
class Game
{
public:
	~Game();

	void loop();

	/* Add a game object to the collection */
	void addGameObject(GameObject* g);
	void addPlayer(Character*);

	/* getters */
	Grid* getGrid() { return _grid; }
	Character* getPlayer(int id) { return _players.at(id); }

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
	void onActivatedGameObject(Event*);
	void onDeactivatedGameObject(Event*);
	void onDie(Event*);

	/* display the current state of the game */
	void displayState(ostream& o = LOGINFO) const; // display the full state of the game (game objects, grid, players ...)
	void displayPlayers(ostream& o = LOGINFO) const; // display players with operator<<
	void displayPlayersList(ostream& o = LOGINFO) const; // just a list with number (used to chose target f.e.)

	/* starting game */
	void initialize();
	void start();
	void beginTurn();
	void endTurn(void* data=nullptr);

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

	deque<Character*> _players;
	Grid* _grid;

	bool _running = true;
	int _turn = 0;
	int _player_turn = 0; // the current player ID which play 

	/* ptr to different services */
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

