#include "FireBallOctopus.h"
#include "ServiceLocator.h"

Texture FireBallOctopus::_basic_player;
double FireBallOctopus::_ratio;
Point FireBallOctopus::PADDING;


FireBallOctopus::FireBallOctopus(Spell* s, Character* caster, SpellTarget* ennemi)
	: OctopusBaby(SPELL_WIDTH, SPELL_HEIGHT), _spell(s), _caster(caster), _ennemi(ennemi)
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

	//depX = GAMEINST->getCurrentPlayer()->getCell()->getPosX();
	//depY = GAMEINST->getCurrentPlayer()->getCell()->getPosY();
	
	positionDepart = (caster->getCell()->getPosX(), caster->getCell()->getPosY()); //Position du caster
	positionArrivee = (ennemi->getCell()->getPosX(), ennemi->getCell()->getPosY()); //Position de l'ennemi

	//Je "crée" un triangle rectangle pour calculer l'hypothénuse, afin d'avoir ainsi l'angle d'orientation et 
	//la valeur des coordonnées en X et en Y lorsque l'on veut faire avancer le sort vers l'ennemi
	largeur = positionDepart.x - positionArrivee.x;
	hauteur = positionDepart.y - positionArrivee.y;

	//Pour savoir où se situe l'ennemi par rapport au joueur
	directionX = largeur / (abs(largeur));
	directionY = hauteur / (abs(hauteur));

	//Defini le pas de déplace de 1 de la source vers la cible
	avancementX = sqrt(largeur*largeur / (largeur*largeur + hauteur*hauteur))*directionX;
	avancementY = sqrt(hauteur*hauteur / (largeur*largeur + hauteur*hauteur))*directionY;

	

	setPosition(positionDepart);
};

FireBallOctopus::~FireBallOctopus()
{};


void FireBallOctopus::update()
{
	int vitesse;
	int nbFrame;
	int duree;
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
		setPosition(getPosition().x + avancementX, getPosition().y + avancementY);
	
	//setPosition(getPosition().x + 0.5, getPosition().y + 0.5); //Sinon ça s'anime pas
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
