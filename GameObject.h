#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "ServiceLocator.h"

using namespace std;
class Game;

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	/* every inherited class has to implement those */
	virtual void update() = 0;
	virtual void initialize() = 0;

	/* those won't be overridden */
	bool isActive() const  { return _active; }
	void setActive(bool a = true);
	bool isToDelete() const { return _to_delete; }
	void setToDelete(bool td = true) { _to_delete = td; }
	int getId() const { return _id; }

	static int getObjectCount()  { return _object_count; }

	friend ostream& operator<<(ostream& o, const GameObject& go);

protected:
	Game * getGameInstance() const { return _gameInstance; }

private:
	/* the totalnumber of GameObject objects */
	static int _object_count;
	/* the next id to assign */
	static int _next_id;
	/* the id of the object */
	int _id;

	bool _active = true;
	bool _to_delete = false;

	Game * _gameInstance;
};

