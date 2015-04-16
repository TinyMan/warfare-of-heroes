#include "TextureManager.h"
#include "ServiceLocator.h"


TextureManager::TextureManager(SDL_Renderer* r)
	: _renderer(r)
{
	loadTexture("Images/PNG/Maquette_menu.png", "menu_mockup");
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
	if (temp != nullptr)
	{
		if (texName.empty())
		{
			// TODO : get texture name from a map filename - texname
			// TODO: remove extension
			texName = filename;
		}
		_textures[texName] = SDL_CreateTextureFromSurface(_renderer, temp);
		SDL_FreeSurface(temp);
		if (_textures[texName])
			return;
	}
	LOGERR << "Cannot load texture " << texName << " from file " << filename << endl;
}

SDL_Texture* TextureManager::operator[](string id)
{
	// TODO : try to load the texture
	if (_textures.count(id) != 1)
		return nullptr;
	return _textures[id];
}