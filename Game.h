#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <list>
#include <deque>
#include <sstream>
#include "CharacterEvents.h"
#include "ServiceLocator.h"
class Octopus;
class GameObject;
class Grid;

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
	Grid* getGrid() const { return _grid; }
	Character* getPlayer(int id) const { return _players.at(id); }
	Character* getCurrentPlayer() const { return _players.at(_player_turn); }
	Octopus* getOctopus() const { return _octopus; }

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

	/* related to the turn */
	void beginTurn();
	void endTurn(void* data=nullptr);
	Uint32 getTimeLeft() const { return  (_turn_max_duration + _turn_start) - TIMESERVICE->time(); }
	Uint32 getTurnStartTime() const { return _turn_start; }

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

	Octopus * _octopus;

	bool _running = true;
	int _turn = 0;
	int _player_turn = 0; // the current player ID which play 

	Uint32 _turn_start = 0; // timestamps of the begining of the turn
	Uint32 _turn_max_duration = 90000; // number of millisecond per turn (max)

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

