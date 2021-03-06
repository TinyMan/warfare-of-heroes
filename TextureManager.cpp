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
	loadTexture("Images/PNG/nothing.png", "spellTest"); //Penser � changer le nom
	loadTexture("Images/PNG/Background_Bouton_Pret.png", "BackgroundReady");
	loadTexture("Images/PNG/Background_Bouton_PretHover.png", "BackgroundReadyHover");
	loadTexture("Images/PNG/FlecheArcher.png", "ArrowArcher");
	loadTexture("Images/PNG/FlecheArcherFeuFrame1.png", "FlammedArrowFrame1");
	loadTexture("Images/PNG/FlecheArcherFeuFrame2.png", "FlammedArrowFrame2");
	loadTexture("Images/PNG/FlecheArcherFeuFrame3.png", "FlammedArrowFrame3");
	loadTexture("Images/PNG/FlecheArcherFeuFrame4.png", "FlammedArrowFrame4");
	loadTexture("Images/PNG/Eruption.png", "Eruption");
	loadTexture("Images/PNG/FireBall.png", "FireBallFrame1");
	loadTexture("Images/PNG/FireBallFrame2.png", "FireBallFrame2");
	loadTexture("Images/PNG/FireBallFrame3.png", "FireBallFrame3");
	loadTexture("Images/PNG/FireBallFrame4.png", "FireBallFrame4");
	loadTexture("Images/PNG/Thunder.png", "Thunder");
	loadTexture("Images/PNG/ThunderFrame1.png", "ThunderFrame1");
	loadTexture("Images/PNG/ThunderFrame2.png", "ThunderFrame2");
	loadTexture("Images/PNG/ThunderFrame3.png", "ThunderFrame3");
	loadTexture("Images/PNG/ThunderFrame4.png", "ThunderFrame4");
	loadTexture("Images/PNG/ThunderFrame5.png", "ThunderFrame5");
	loadTexture("Images/PNG/ThunderFrame6.png", "ThunderFrame6");
	loadTexture("Images/PNG/ThunderFrame7.png", "ThunderFrame7");
	loadTexture("Images/PNG/Roots.png", "Root");
	loadTexture("Images/PNG/SwordOfDestiny.png", "SwordDestiny");
	loadTexture("Images/PNG/VoleeFleches.png", "VoleeFleches");
	loadTexture("Images/PNG/MuteMusicOff.png", "MuteMusicOff");
	loadTexture("Images/PNG/MuteMusicOn.png", "MuteMusicOn");
	loadTexture("Images/PNG/SwordForwardFrame1.png", "SwordForwardFrame1");
	loadTexture("Images/PNG/SwordForwardFrame2.png", "SwordForwardFrame2");
	loadTexture("Images/PNG/SwordForwardFrame3.png", "SwordForwardFrame3");
	loadTexture("Images/PNG/SwordForwardFrame4.png", "SwordForwardFrame4");
	loadTexture("Images/PNG/SwordForwardFrame5.png", "SwordForwardFrame5");
	loadTexture("Images/PNG/SwordForwardFrame6.png", "SwordForwardFrame6");
	loadTexture("Images/PNG/SwordForwardFrame7.png", "SwordForwardFrame7");
	loadTexture("Images/PNG/SwordForwardFrame8.png", "SwordForwardFrame8");
	loadTexture("Images/PNG/SwordForwardFrame9.png", "SwordForwardFrame9");
	loadTexture("Images/PNG/SwordForwardFrame10.png", "SwordForwardFrame10");
	loadTexture("Images/PNG/VoleeFlechesFrame1.png", "VoleeFlechesFrame1");
	loadTexture("Images/PNG/VoleeFlechesFrame2.png", "VoleeFlechesFrame2");
	loadTexture("Images/PNG/VoleeFlechesFrame3.png", "VoleeFlechesFrame3");
	loadTexture("Images/PNG/VoleeFlechesFrame4.png", "VoleeFlechesFrame4");
	loadTexture("Images/PNG/VoleeFlechesFrame5.png", "VoleeFlechesFrame5");
	loadTexture("Images/PNG/VoleeFlechesFrame6.png", "VoleeFlechesFrame6");
	loadTexture("Images/PNG/VoleeFlechesFrame7.png", "VoleeFlechesFrame7");
	loadTexture("Images/PNG/VoleeFlechesFrame8.png", "VoleeFlechesFrame8");
	loadTexture("Images/PNG/VoleeFlechesFrame9.png", "VoleeFlechesFrame9");
	loadTexture("Images/PNG/VoleeFlechesFrame10.png", "VoleeFlechesFrame10");
	loadTexture("Images/PNG/FondPopup.png", "FondPopup");


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
	{
		LOGERR << "Could not find texture " << id << endl;
		return nullptr;
	}
	return _textures[id];
}