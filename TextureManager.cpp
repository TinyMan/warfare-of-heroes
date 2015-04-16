#include "TextureManager.h"
#include "ServiceLocator.h"


TextureManager::TextureManager(SDL_Renderer* r)
	: _renderer(r)
{
}


TextureManager::~TextureManager()
{
	for (auto t : _textures)
	{
		SDL_DestroyTexture(t.second);
	}
}

void TextureManager::loadTexture(string filename, string texName)
{
	if (_renderer == nullptr)
		return;
	SDL_Surface* temp = IMG_Load(filename.c_str());
	if (texName.empty())
	{
		// TODO : get texture name from a map filename - texname
		// TODO: remove extension
		texName = filename;
	}
	_textures[texName] = SDL_CreateTextureFromSurface(_renderer, temp);
	SDL_FreeSurface(temp);
}

SDL_Texture* TextureManager::operator[](string id)
{
	// TODO : try to load the texture
	if (_textures.count(id) != 1)
		return nullptr;
	return _textures[id];
}