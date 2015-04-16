#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <iostream>
#include "ServiceLocator.h"

using namespace std;

class TextureManager
{
public:
	TextureManager(SDL_Renderer* renderer);
	virtual ~TextureManager();

	void loadTexture(string filename, string texName = "");

	void setRenderer(SDL_Renderer* r) { _renderer = r; }
	SDL_Renderer* getRenderer() const { return _renderer; }

	SDL_Texture * operator[](string textureName);
private:
	SDL_Renderer * _renderer = nullptr;
	map<string, SDL_Texture*> _textures;
	// TODO : add a map texture name <-> file name

};

