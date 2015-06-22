#include "TextureManager.h"
#include "ServiceLocator.h"


TextureManager::TextureManager(SDL_Renderer* r)
: _renderer(r)
{
	loadTexture("Images/PNG/Maquette_menu.png", "menu_mockup");
	loadTexture("Images/PNG/path3346-6.png", "player_basic");
	loadTexture("Images/PNG/Knight.png", "knight");
	loadTexture("Images/PNG/Mage.png", "mage");
	loadTexture("Images/PNG/Archer.png", "archer");
	loadTexture("Images/PNG/fondecrou.png", "fondecrou");
	loadTexture("Images/PNG/fondrectangle.png", "fondrectangle");
	loadTexture("Images/PNG/Arbre.png", "obstacle_0");
	loadTexture("Images/PNG/Cailloux.png", "obstacle_1");
	loadTexture("Images/PNG/Mage.png", "icon_mage");
	loadTexture("Images/PNG/Archer.png", "icon_archer");
	loadTexture("Images/PNG/Knight.png", "icon_knight");
	loadTexture("Images/PNG/Sort1.png", "icon_spell_10");
	loadTexture("Images/PNG/sort2.png", "icon_spell_7");
	loadTexture("Images/PNG/SpellRoots.png", "icon_spell_11");
	loadTexture("Images/PNG/sort4.png", "icon_spell_6");
	loadTexture("Images/PNG/sort5.png", "icon_spell_12");
	loadTexture("Images/PNG/sort6.png", "icon_spell_2");
	loadTexture("Images/PNG/sort7.png", "icon_spell_9");
	loadTexture("Images/PNG/SpellSwordOfDestiny.png", "icon_spell_8"); 
	loadTexture("Images/PNG/SpellDash.png", "icon_spell_5");
	loadTexture("Images/PNG/sort10.png", "icon_spell_1"); 
	loadTexture("Images/PNG/sort11.png", "icon_spell_4");
	loadTexture("Images/PNG/sort12.png", "icon_spell_3");
	loadTexture("Images/PNG/bgPlayerLeft.png", "bgPLeft"); 
	loadTexture("Images/PNG/bgPlayerRight.png", "bgPRight");
	loadTexture("Images/PNG/FondChrono.png", "bgChrono");
	loadTexture("Images/PNG/FondSortEnBas.png", "bgSpells");
	loadTexture("Images/PNG/FondChronoHover.png", "bgChronoHover");
	loadTexture("Images/PNG/ParcheminV2.png", "parchemin");
	loadTexture("Images/PNG/MenuSelectionBackGround.png", "menuSelectBG");
	loadTexture("Images/PNG/flechedroite.png", "flecheD");
	loadTexture("Images/PNG/flechegauche.png", "flecheG");
	loadTexture("Images/PNG/FondHautSelection.png", "menuSelectTopBG");
	loadTexture("Images/PNG/nothing.png", "spellTest"); //Penser à changer le nom
	loadTexture("Images/PNG/Background_Bouton_Pret.png", "BackgroundReady");
	loadTexture("Images/PNG/Background_Bouton_PretHover.png", "BackgroundReadyHover");
	loadTexture("Images/PNG/FlecheArcherFeu.png", "FlecheArcher");
	loadTexture("Images/PNG/Eruption.png", "Eruption");
	loadTexture("Images/PNG/FireBall.png", "FireBall");
	loadTexture("Images/PNG/Thunder.png", "Thunder");
	loadTexture("Images/PNG/Roots.png", "Root");
	loadTexture("Images/PNG/SwordOfDestiny.png", "SwordDestiny");
	loadTexture("Images/PNG/VoleeFleches.png", "VoleeFleches");


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