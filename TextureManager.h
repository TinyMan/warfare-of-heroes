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
	TextureManager();
	virtual ~TextureManager();

	void loadTexture(string filename, string texName = "");

private:
	map<string, SDL_Texture*> _textures;

};

