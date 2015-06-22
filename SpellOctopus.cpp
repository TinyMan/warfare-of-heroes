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

	origin_cell = GAMEINST->getCurrentPlayer()->getCell();
	destination_cell = GAMEINST->getGrid()->getCell(c);
	nomduSpell = spellN;

	largeur = (origin_cell->getPosX()) - (destination_cell->getPosX());
	hauteur = (origin_cell->getPosY()) - (destination_cell->getPosY());

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
	int vitesse = 200;
	if (TIMESERVICE->getFrameTime() % vitesse >= 0 && TIMESERVICE->getFrameTime() % vitesse < vitesse/3)
		_basic_player=(*ServiceLocator::getTextureManager())["FireBall"];
	else if (TIMESERVICE->getFrameTime() % vitesse >= vitesse / 3 && TIMESERVICE->getFrameTime() % vitesse < vitesse*2/3)
		_basic_player = (*ServiceLocator::getTextureManager())["Thunder"];
	else if (TIMESERVICE->getFrameTime() % vitesse >= vitesse*2/3 && TIMESERVICE->getFrameTime() % vitesse < vitesse - 1)
		_basic_player = (*ServiceLocator::getTextureManager())["SwordDestiny"];
	//_basic_player = (*ServiceLocator::getTextureManager())["Thunder"];
		setPosition(getPosition().x + 1, getPosition().y + 1);
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
