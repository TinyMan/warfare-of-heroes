#include "Game.h"
#include "SDLEvents.h"
#include "Panel.h"
#include "Button.h"
#include "Octopus.h"
#include "GameObject.h"
#include "Character.h"
#include "Grid.h"
#include "Tooltip.h"
#include "GridOctopus.h"
#include "Chrono.h"
#include "RecapOctopus.h"
#include "Archer.h"
#include "Mage.h"
#include "Knight.h"
#include "SpellRecap.h"
#include "PlayerOctopus.h"
#include "ObstacleOctopus.h"

Game* Game::_instance = nullptr;

Game::Game()
{
	/* instanciate services */
	_eventService = new EventService();
	_logService = new LogService("log.txt", true);
	_timeService = new TimeService();
	_userInterface = new UserInterface();
	/* and provide them */
	ServiceLocator::provide(_eventService);
	ServiceLocator::provide(_logService);
	ServiceLocator::provide(_timeService);
	ServiceLocator::provide(_userInterface);

	/* setup event listenenrs */
	_eventService->listen(typeid(Events::GameObjectEvents::ActivateEvent), EventCallback(&Game::onActivatedGameObject, this));
	_eventService->listen(typeid(Events::GameObjectEvents::DeactivateEvent), EventCallback(&Game::onDeactivatedGameObject, this));
	_eventService->listen(typeid(Events::CharacterEvents::DieEvent), EventCallback(&Game::onDie, this));
	
	/* generate basic game objects */
	_grid = new Grid();
	_octopus = new Octopus();

}

void Game::initialize()
{

	Grid* grid = getGrid();
	grid->generateObstacle();
		
	_octopus->initialize();

	// used to navigateto another frame
	auto navigationLambda = [=](Panel* to, Event* e)
	{
		_octopus->setFrameAsync(to);
	};
	/* creation of different frames */
	Panel* menu_root = new Panel();
	Panel* menu_1 = new Panel();

	/* creation of menu */
	Panel* menu_root_inside = new Panel(300, 100 + 75 + 75 + 75 + 75); // 4 boutons de hauteur 50, espacements de 25 entre les boutons et 50 avec les bords du container +25 devant quitter
	menu_root->add(menu_root_inside, (Alignment::CENTERY | Alignment::CENTERX));
	Texture menu_inside_background(300, 500);
	menu_inside_background.fill(_octopus->getRenderer(), Color::GREEN);
	menu_root_inside->setBackground(menu_inside_background);

	Button* button_1 = new Button(150, 50);
	menu_root_inside->add(button_1, Alignment::CENTERX);
	button_1->setPositionY(50);
	button_1->setText("Play");
	button_1->setTextColor(Color(240,190));
	button_1->setTextAlignment(Alignment::CENTERX | Alignment::CENTERY);
	button_1->Clickable::setCallback(new EventCallback([=](Event*){ start(new Mage(-13,0), new Archer(13,0)); }));

	Button* button_quit = button_1->clone();
	menu_root_inside->add(button_quit, Alignment::CENTERX);
	button_quit->setPositionY(75 + 75 + 75 + 75);
	button_quit->setText("Exit");
	button_quit->Clickable::setCallback(new EventCallback(&Game::stop, this));

	Button* button_2 = button_quit->clone();
	menu_root_inside->add(button_2, Alignment::CENTERX);
	button_2->setPositionY(50 + 75);
	button_2->setText("How to Play");

	Button* button_3 = button_2->clone();
	menu_root_inside->add(button_3, Alignment::CENTERX);
	button_3->setPositionY(50 + 75 + 75);
	button_3->setText("Settings");

	Panel* menu_1_inside = new Panel(300, 500);
	menu_1->add(menu_1_inside, Alignment::CENTERX | Alignment::CENTERY);
	menu_1_inside->setBackground(menu_inside_background);


	Tooltip* tt = new Tooltip(500, 200);
	tt->setBackground(Texture(500, 200, Color::RED, _octopus->getRenderer()));
	tt->setText("Tooltip exemple\nThis is \na multiline \nexample of text\n");
	tt->setTextSize(24);
	tt->setTitle("Tooltip");
	tt->setTitleColor(Color::GREEN);
	menu_root->add(tt);
	tt->anchor(button_1);

	
	_octopus->setFrame(menu_root);

}
Game::~Game()
{
	/* destroy all last game objects */
	while (!_gameObjects.empty())
	{
		delete _gameObjects.front();
		_gameObjects.pop_front();
	}
	delete _octopus;
	ServiceLocator::cleanup();
}

void Game::loop()
{
	SDL_Event e;
	Event* ev;
	Uint32 last_time = 0;
	Uint32 accumulator = 0;

	//cout << "Main loop !" << endl;

	while (_running)
	{
		/* TODO: BEGIN FRAME */
		_timeService->beginFrame();
		/* TODO: PROCESS USER INPUT */
		while (accumulator < 1000 / fps_limit){
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT)
				{
					//Quit the program
					stop();
				}
				ev = SDLEvents::createEventFromSDLEvent(&e);
				if (ev)
					_eventService->dispatch(ev);
			}
			// sleeping
			SDL_Delay(((1000 / fps_limit) - accumulator) / 5);
			// mise a jour du temps
			accumulator += SDL_GetTicks() - last_time - accumulator;
		}

		/* Update */
		_timeService->update();
		_octopus->update();
		/* TODO: UPDATE */
		this->update();

		/*

		cout << "Number of active game objects: " << getNbActiveGObjects() << endl;
		*/

		// on m�morise le possible retard qu'on a prit
		accumulator -= 1000 / fps_limit;

		// on indique le dernier instant d'affichage
		last_time = SDL_GetTicks();

		/* TODO: RENDER */
		_octopus->render();
		/* TODO: END FRAME */
		_timeService->endFrame();
	}
}

void Game::addGameObject(GameObject* g)
{
	ServiceLocator::getLogService()->info << "Adding new game object to collection" << endl;
	/* we do not want null ptr in the list */
	if (g == nullptr)
		return;
	/* if it is active add it to te front */
	if (g->isActive())
	{
		_nb_active_gobjects++;
		_gameObjects.push_front(g);
	}
	else /* else add it to the back */
		_gameObjects.push_back(g);
}

void Game::addPlayer(Character* c)
{
	_players.push_back(c);
}
void Game::onDeactivatedGameObject(Event*)
{
	ServiceLocator::getLogService()->info << "Catching ev: game object deactivated" << endl;
	_gameObjects_dirty = true;
	if (_nb_active_gobjects > 0) /* prevent silly errors */
		_nb_active_gobjects--;
}
void Game::onActivatedGameObject(Event*)
{
	ServiceLocator::getLogService()->info << "Catching ev: game object activated" << endl;
	_gameObjects_dirty = true;
	_nb_active_gobjects++;
}
void Game::onDie(Event* data)
{
	if (data == nullptr)
		return;
	char a;
	Character* c = (Character*)((DieEvent*)data)->getCharacter();
	LOGINFO << c->getName() << " died !" << endl;	
	LOGINFO << "Do you want to replay (y/n) ?" << endl;
	cin >> a;
	switch (a)
	{
	case 'y':
		// TODO: reset game 
		break;
	default:
		stop();
		break;
	}
}
void Game::displayState(ostream& o) const
{
	stringstream sstm;
	o << "Currently " << _gameObjects.size() << " game objects in the list." << endl;

	/*for (auto& e : _gameObjects)
	{
		o << *e << endl;
	}*/
	displayPlayers(o);
	o << "Grid: " << endl;
	_grid->display(o);
}
void Game::displayPlayers(ostream& o) const
{
	o << "Players: " << endl;
	for (auto& e : _players)
	{
		o << *e;
		o << "<--------------------------------->" << endl;
	}
	
}
void Game::displayPlayersList(ostream& o) const
{
	int i = 0;
	o << "Players list: " << endl;
	for (auto& e : _players)
	{
		o << i++ << ": " << e->getName() << endl;
	}
}

void Game::update()
{
	/* sorting the list of game objects */
	if (_gameObjects_dirty)
	{
		_logService->info << "Game Objects list is dirty !" << endl;
		_gameObjects.sort(compare);
		_gameObjects_dirty = false;
	}
}

void Game::handleUserInput()
{
	// TODO : add textmode gameplay
	int choice = 0;
	LOGINFO << "------------------------" << endl;
	LOGINFO << "Turn " << _turn << ", player " << _player_turn << " (" << _players.at(_player_turn)->getName() << "): " << endl;
	LOGINFO << *UI << endl;


	cin >> choice;
	UI->handleChoice(choice);
}
void Game::start(Character* player1, Character* player2)
{
	LOGINFO << "Starting the game !" << endl;
	//addGameObject(player1, player2);
	addPlayer(player1);
	addPlayer(player2);

	Panel* game_frame = new Panel();
	game_frame->setBgColor(Color::WHITE);

	/* creation of game frame */
	Panel * game_inside = new Panel(800, 600);
	game_inside->setBgColor(Color::WHITE);
	game_frame->add(game_inside, Alignment::TOP | Alignment::CENTERX);

	GridOctopus* gridO = new GridOctopus(_grid, 800, 400);
	game_inside->add(gridO, Alignment::CENTERX | Alignment::CENTERY);

	PlayerOctopus* p = new PlayerOctopus(_players[0], gridO);
	PlayerOctopus* p1 = new PlayerOctopus(_players[1], gridO);

	game_inside->add(p);
	game_inside->add(p1);


	for (auto& c : getGrid()->getObstacles())
	{
		game_inside->add(new ObstacleOctopus(c, gridO));
	}

	Chrono* chrono = new Chrono();
	game_inside->add(chrono, Alignment::TOP | Alignment::CENTERX);

	RecapOctopus* recap1 = new RecapOctopus(0);
	RecapOctopus* recap3 = new RecapOctopus(1);
	game_frame->add(recap1, Alignment::TOP | Alignment::LEFT);
	game_frame->add(recap3, Alignment::TOP | Alignment::RIGHT);

	SpellRecap* sr = new SpellRecap(_players[0], gridO);
	SpellRecap* sr1 = new SpellRecap(_players[1], gridO);
	game_frame->add(sr, Alignment::BOTTOM | Alignment::LEFT);
	game_frame->add(sr1, Alignment::BOTTOM | Alignment::LEFT);
	_octopus->setFrameAsync(game_frame);
	beginTurn();
}
void Game::beginTurn()
{
	LOGINFO << "Begining turn of " << _players.at(_player_turn)->getName() << endl;
	UI->addAction(Action(Callback(&Game::stop, this), "Quit"));
	UI->addAction(Action(Callback(&Game::endTurn, this), "I'm done"));
	_players.at(_player_turn)->beginTurn();
	_grid->beginTurn();
	_turn_start = TIMESERVICE->time();
	_endOfTurn_timeout = TIMESERVICE->setTimeout(_turn_max_duration, Callback(&Game::endTurn, this));
	(new BeginTurnEvent(_players.at(_player_turn)))->dispatch();
}
void Game::endTurn(void* )
{
	_players.at(_player_turn)->endTurn();
	_turn += _player_turn;
	_player_turn = _player_turn == 0 ? 1 : 0;
	UI->clear();
	TIMESERVICE->removeTimeout(_endOfTurn_timeout);
	beginTurn();
}