#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <list>

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

	void addGameObject(GameObject* g);
	int getNbActiveGObjects() const { return _nb_active_gobjects; }

private:
	/* the collection of all game objects, sorted with the active ones on the front and the inactive ones after them */
	list<GameObject*> _gameObjects;
	/* number of active gameobjects */
	int _nb_active_gobjects = 0;



	/* update its state, delete objects marked etc ... */
	void update();
};

