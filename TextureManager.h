#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <iostream>
#include "Texture.h"

using namespace std;

class TextureManager
{
public:
	TextureManager(SDL_Renderer* renderer);
	virtual ~TextureManager();

	void loadTexture(string filename, string texName = "");

	void setRenderer(SDL_Renderer* r) { _renderer = r; }
	SDL_Renderer* getRenderer() const { return _renderer; }

	Texture operator[](string textureName);
private:
	SDL_Renderer * _renderer = nullptr;
	map<string, Texture> _textures;
	// TODO : add a map texture name <-> file name

};

