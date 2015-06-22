#include "FireBallOctopus.h"
#include "ServiceLocator.h"
#include "Character.h"

Texture FireBallOctopus::_basic_player;
double FireBallOctopus::_ratio;
Point FireBallOctopus::PADDING;


FireBallOctopus::FireBallOctopus(Spell* s, Character* caster, SpellTarget* ennemi)//, Grid* grid)
	: OctopusBaby(SPELL_WIDTH, SPELL_HEIGHT), _spell(s), _caster(caster), _ennemi(ennemi)//, _grid(grid)
{
	if (!_basic_player.valid()){
		_basic_player = (*ServiceLocator::getTextureManager())["spellTest"];

		// compute ratio
		double ratiox = (double)_relative_rect.w / _basic_player.getWidth();
		double ratioy = (double)_relative_rect.h / _basic_player.getHeight();
		_ratio = min(ratioy, ratiox);

		// calculate padding
		PADDING = Point(-_basic_player.getWidth() * _ratio / 2, -_basic_player.getHeight() * _ratio + 7);
	}
	setBgColor(Color::TRANSPARENT);
	_basic_player = (*ServiceLocator::getTextureManager())["spellTest"];

	//depX = GAMEINST->getCurrentPlayer()->getCell()->getPosX();
	//depY = GAMEINST->getCurrentPlayer()->getCell()->getPosY();
	
	_caster = caster;
	_ennemi = ennemi;


	//positionDepart = (caster->getCell()->getPosX(), caster->getCell()->getPosY()); //Position du caster
	//positionArrivee = (ennemi->getCell()->getPosX(), ennemi->getCell()->getPosY()); //Position de l'ennemi

	PlayerOctopus* playerCaster = GAMEINST->getPlayerOcto(_caster->getId());
	int idEnnemi;
	if (_caster->getId() == 0)
		idEnnemi = 1;
	else if (_caster->getId() == 1)
		idEnnemi = 0;
	PlayerOctopus* playerTarget = GAMEINST->getPlayerOcto(idEnnemi);
	//playerCaster->getAbsolutePosition();
	positionDepart = playerCaster->getAbsolutePosition();
	positionArrivee = playerTarget->getAbsolutePosition();
	
	//Je "cr�e" un triangle rectangle pour calculer l'hypoth�nuse, afin d'avoir ainsi l'angle d'orientation et 
	//la valeur des coordonn�es en X et en Y lorsque l'on veut faire avancer le sort vers l'ennemi
	largeur = positionDepart.x - positionArrivee.x;
	hauteur = positionDepart.y - positionArrivee.y;

	//Pour savoir o� se situe l'ennemi par rapport au joueur
	directionX = largeur / (abs(largeur));
	directionY = hauteur / (abs(hauteur));
	
	

	//Defini le pas de d�place de 1 de la source vers la cible
	avancementX = sqrt(largeur*largeur / (largeur*largeur + hauteur*hauteur))*directionX;
	avancementY = sqrt(hauteur*hauteur / (largeur*largeur + hauteur*hauteur))*directionY;
	
	setActive(true);
	
	setPositionX(50);
	setPositionY(50);
	//setPositionX(caster->getCell()->getPosX());
	//setPositionY(caster->getCell()->getPosY());
	//setPosition(caster->getCell()->getPosX(), caster->getCell()->getPosY());
};

FireBallOctopus::~FireBallOctopus()
{};


void FireBallOctopus::update()
{
	Uint32 vitesse;
	Uint32 nbFrame;
	Uint32 duree;
	vitesse = 200;
	nbFrame = 4;
	//duree = TIMESERVICE->getFrameTime() + 1000;
		//Animation des frames
		if (TIMESERVICE->getFrameTime() % vitesse >= 0 && TIMESERVICE->getFrameTime() % vitesse < vitesse / nbFrame)
			_basic_player = (*ServiceLocator::getTextureManager())["FireBall"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= vitesse / nbFrame && TIMESERVICE->getFrameTime() % vitesse < vitesse * 2 / nbFrame)
			_basic_player = (*ServiceLocator::getTextureManager())["FireBallFrame2"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= vitesse * 2 / nbFrame && TIMESERVICE->getFrameTime() % vitesse < vitesse * 3 / nbFrame)
			_basic_player = (*ServiceLocator::getTextureManager())["FireBallFrame3"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= vitesse * 3 / nbFrame && TIMESERVICE->getFrameTime() % vitesse < vitesse - 1)
			_basic_player = (*ServiceLocator::getTextureManager())["FireBallFrame4"];

		//Deplacement du sort
		//setPosition(getPosition().x + avancementX, getPosition().y + avancementY);
	
	setPosition(getPosition().x + 0.5, getPosition().y + 0.5); //Sinon �a s'anime pas
}

void FireBallOctopus::setPosition(Point pos)
{
	if (pos != getPosition())
	{
		OctopusBaby::setPosition((int)pos.x, (int)pos.y);
	}
}

void FireBallOctopus::internalRender(SDL_Renderer* r, bool force)
{
	if (isActive())
	{
		bool d = (force || isDirty());
		if (d)
		{
			SDL_Rect dst = _relative_rect;
			dst.w = int(_ratio * _basic_player.getWidth());
			dst.h = int(_ratio * _basic_player.getHeight());
			dst.x = 0;
			dst.y = 0;
			SDL_RenderCopyEx(r, _basic_player, nullptr, &dst, 0.0, nullptr, (SDL_RendererFlip)orientation);

		}
	}
}
