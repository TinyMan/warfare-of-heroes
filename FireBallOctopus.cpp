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

	_basic_player = (*ServiceLocator::getTextureManager())["spellTest"]; //Oui, c'est une teub, si vous la voyez c'est qu'il y a une couille dans le code

	_caster = caster;
	_ennemi = ennemi;

	int idCaster;
	int idEnnemi;

	//Temps que dure l'animation (détermine la vitesse et quand s'arrête l'animation)
	tempsAnimation = 2000;
	finAnimation = TIMESERVICE->time() + tempsAnimation;

	//Permet de savoir quel PlayerOctopus du jeu représente le caster (et en même temps celui de la target)
	Character* tempChara = GAMEINST->getPlayer(0);
	if (tempChara == caster)
	{
		idCaster = 0;
		idEnnemi = 1;
	}
	else
	{
		idCaster = 1;
		idEnnemi = 0;
	}
	

	PlayerOctopus* playerCaster = GAMEINST->getPlayerOcto(idCaster);
	PlayerOctopus* playerTarget = GAMEINST->getPlayerOcto(idEnnemi);
	//playerCaster->getAbsolutePosition();
	positionDepart = playerCaster->getAbsolutePosition();
	positionArrivee = playerTarget->getAbsolutePosition();
	
	//Distance entre le casteur et la target
	largeur = (positionDepart.x - positionArrivee.x)*(-1);
	hauteur = (positionDepart.y - positionArrivee.y)*(-1);

	//A diviser par le nombre de milliseconde que doit durer l'animation (ici 2000)
	avancementX = largeur / tempsAnimation;
	avancementY = hauteur / tempsAnimation;

	avancementX = static_cast<int>(avancementX * 1000) % 5;
	avancementY = static_cast<int>(avancementY * 1000) % 5;

	LOGINFO << "AvancementX : " << avancementX << " AvancementY : " << avancementY << endl;

	setActive(true); //OBLIGATOIRE, sinon bah ça s'affiche pas
	
	setPositionX(positionDepart.x-200); //Obligé de mettre un moins, sinon ça coucouille (va savoir pourquoi)
	setPositionY(positionDepart.y);
};

FireBallOctopus::~FireBallOctopus()
{};


void FireBallOctopus::update()
{
	if (TIMESERVICE->time() >= finAnimation)
		setActive(false);
	Uint32 vitesse;
	Uint32 nbFrame;
	vitesse = 200;
	nbFrame = 4;
		//Animation des frames
	//La vitesse correspond au temps total de l'animation en milliseconde
	//Ici, je change d'image tous les 1/4 de temps
		if (TIMESERVICE->getFrameTime() % vitesse >= 0 && TIMESERVICE->getFrameTime() % vitesse < vitesse / nbFrame)
			_basic_player = (*ServiceLocator::getTextureManager())["FireBall"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= vitesse / nbFrame && TIMESERVICE->getFrameTime() % vitesse < vitesse * 2 / nbFrame)
			_basic_player = (*ServiceLocator::getTextureManager())["FireBallFrame2"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= vitesse * 2 / nbFrame && TIMESERVICE->getFrameTime() % vitesse < vitesse * 3 / nbFrame)
			_basic_player = (*ServiceLocator::getTextureManager())["FireBallFrame3"];
		else if (TIMESERVICE->getFrameTime() % vitesse >= vitesse * 3 / nbFrame && TIMESERVICE->getFrameTime() % vitesse < vitesse - 1)
			_basic_player = (*ServiceLocator::getTextureManager())["FireBallFrame4"];

		/*
		Point origin_pos = positionDepart;
		Point dest_pos = positionArrivee;
		Point delta = abs(origin_pos - dest_pos);
		Point middle = (origin_pos - dest_pos) / 2;
		Uint32 movement_begin = TIMESERVICE->time() + tempsAnimation;
		Uint32 dt = (TIMESERVICE->time() - movement_begin);
		Point step = ((dest_pos - origin_pos) * dt) / tempsAnimation;
		Point newPos = origin_pos + step;*/

		//Deplacement du sort
		//setPosition(newPos);

		setPosition(getPosition().x + avancementX, getPosition().y + avancementY);
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
