#include "SpellOctopus.h"
#include "ServiceLocator.h"

Texture SpellOctopus::_basic_player;
double SpellOctopus::_ratio;
Point SpellOctopus::PADDING;


SpellOctopus::SpellOctopus(string spellN, unsigned int c, GridOctopus* grid)
	: OctopusBaby(SPELL_WIDTH, SPELL_HEIGHT)
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

	origin_cell = GAMEINST->getCurrentPlayer()->getCell(); //Position du caster
	destination_cell = GAMEINST->getGrid()->getCell(c); //Position de l'ennemi
	nomduSpell = spellN;

	//Je "crée" un triangle rectangle pour calculer l'hypothénuse, afin d'avoir ainsi l'angle d'orientation et 
	//la valeur des coordonnées en X et en Y lorsque l'on veut faire avancer le sort vers l'ennemi
	largeur = (origin_cell->getPosX()) - (destination_cell->getPosX()); 
	hauteur = (origin_cell->getPosY()) - (destination_cell->getPosY());

	//Pour savoir où se situe l'ennemi par rapport au joueur
	directionX = largeur / (abs(largeur));
	directionY = hauteur / (abs(hauteur));

	//Defini le pas de déplace de 1 de la source vers la cible
	avancementX = sqrt(largeur*largeur / (largeur*largeur + hauteur*hauteur))*directionX;
	avancementY = sqrt(hauteur*hauteur / (largeur*largeur + hauteur*hauteur))*directionY;

	//setAlpha(0);

	setPosition(origin_cell->getPosX(), origin_cell->getPosY());
};

SpellOctopus::~SpellOctopus()
{};

/*void SpellOctopus::update()
{
	while (abs(origin_cell->getPosX() - destination_cell->getPosX())>5 && abs(origin_cell->getPosY() - destination_cell->getPosY())>5)
	{
		depX = getPosition().x;
		depY = getPosition().y;
		Point avance = (depX + avancementX, depY + avancementY);
		setPosition(avance);
	}
}*/

void SpellOctopus::update()
{
	int vitesse;
	int nbFrame;
	int duree;
	nomduSpell = "thunder"; //a changer pour voir les autres sorts
	if (nomduSpell == "fireball") // Sort boule de feu
	{
		vitesse = 200;
		nbFrame = 4;
		if (TIMESERVICE->getFrameTime() % vitesse >= 0 && TIMESERVICE->getFrameTime() % vitesse < vitesse / nbFrame)
			_basic_player = (*ServiceLocator::getTextureManager())["FireBall"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= vitesse / nbFrame && TIMESERVICE->getFrameTime() % vitesse < vitesse * 2 / nbFrame)
			_basic_player = (*ServiceLocator::getTextureManager())["FireBallFrame2"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= vitesse * 2 / nbFrame && TIMESERVICE->getFrameTime() % vitesse < vitesse * 3 / nbFrame)
			_basic_player = (*ServiceLocator::getTextureManager())["FireBallFrame3"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= vitesse * 3 / nbFrame && TIMESERVICE->getFrameTime() % vitesse < vitesse - 1)
			_basic_player = (*ServiceLocator::getTextureManager())["FireBallFrame4"];
	}
	if (nomduSpell == "thunder") // Sort Tonnerre
	{
		vitesse = 8000;
		nbFrame = 7;
		duree = 8000;
		if (TIMESERVICE->getFrameTime() % vitesse >= 0 && TIMESERVICE->getFrameTime() % vitesse < 100)
			_basic_player = (*ServiceLocator::getTextureManager())["ThunderFrame1"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= 100 && TIMESERVICE->getFrameTime() % vitesse < 200)
			_basic_player = (*ServiceLocator::getTextureManager())["ThunderFrame2"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= 200 && TIMESERVICE->getFrameTime() % vitesse < 300)
			_basic_player = (*ServiceLocator::getTextureManager())["ThunderFrame3"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= 300 && TIMESERVICE->getFrameTime() % vitesse < 400)
			_basic_player = (*ServiceLocator::getTextureManager())["ThunderFrame4"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= 400 && TIMESERVICE->getFrameTime() % vitesse < 2000)
			_basic_player = (*ServiceLocator::getTextureManager())["ThunderFrame5"];
		else if (TIMESERVICE->getFrameTime() % vitesse >=2000 && TIMESERVICE->getFrameTime() % vitesse < 2500)
			_basic_player = (*ServiceLocator::getTextureManager())["ThunderFrame6"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= 2500 && TIMESERVICE->getFrameTime() % vitesse < 4000)
			_basic_player = (*ServiceLocator::getTextureManager())["ThunderFrame5"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= 4000 && TIMESERVICE->getFrameTime() % vitesse < 4500)
			_basic_player = (*ServiceLocator::getTextureManager())["ThunderFrame7"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= 4500 && TIMESERVICE->getFrameTime() % vitesse < 7600)
			_basic_player = (*ServiceLocator::getTextureManager())["ThunderFrame5"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= 7600 && TIMESERVICE->getFrameTime() % vitesse < 7700)
			_basic_player = (*ServiceLocator::getTextureManager())["ThunderFrame4"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= 7700 && TIMESERVICE->getFrameTime() % vitesse < 7800)
			_basic_player = (*ServiceLocator::getTextureManager())["ThunderFrame3"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= 7800 && TIMESERVICE->getFrameTime() % vitesse < 7900)
			_basic_player = (*ServiceLocator::getTextureManager())["ThunderFrame2"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= 7900 && TIMESERVICE->getFrameTime() % vitesse < 7999)
			_basic_player = (*ServiceLocator::getTextureManager())["ThunderFrame1"];
	}
	//_basic_player = (*ServiceLocator::getTextureManager())["Thunder"];
		setPosition(getPosition().x + 0.5, getPosition().y + 0.5); //Sinon ça s'anime pas
}

void SpellOctopus::setPosition(Point pos)
{
	if (pos != getPosition())
	{
		OctopusBaby::setPosition((int)pos.x, (int)pos.y);
	}
}

void SpellOctopus::internalRender(SDL_Renderer* r, bool force)
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
