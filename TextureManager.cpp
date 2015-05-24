#include "TextureManager.h"
#include "ServiceLocator.h"


TextureManager::TextureManager(SDL_Renderer* r)
	: _renderer(r)
{
	loadTexture("Images/PNG/Maquette_menu.png", "menu_mockup");
	loadTexture("Images/PNG/path3346-6.png", "player_basic");
	loadTexture("Images/PNG/Chevalier_Exemple.png", "knight");
	loadTexture("Images/PNG/fondecrou.png", "fondecrou");
	loadTexture("Images/PNG/fondrectangle.png", "fondrectangle");
	
}


TextureManager::~TextureManager()
{
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
		{
			SDL_SetTextureBlendMode(_textures[texName], SDL_BLENDMODE_BLEND);
			return;
		}
	}
	LOGERR << "Cannot load texture " << texName << " from file " << filename << endl;
}

Texture TextureManager::operator[](string id)
{
	// TODO : try to load the texture
	if (_textures.count(id) != 1)
		return nullptr;
	return _textures[id];
}