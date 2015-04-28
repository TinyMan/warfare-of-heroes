#include "Game.h"
#include "SDLEvents.h"
#include "Panel.h"
#include "Button.h"
#include "Octopus.h"
#include "GameObject.h"
#include "Character.h"
#include "Grid.h"
#include "Tooltip.h"

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
	_octopus->initialize();

	/* creation of menu */
	// used to navigateto another frame
	auto navigationLambda = [=](Panel* to, Event* e)
	{
		_octopus->setFrameAsync(to);
	};
	Panel* menu_root = new Panel();
	Panel* menu_1 = new Panel();

	Panel* menu_root_inside = new Panel(300, 100+75+75+75+75); // 4 boutons de hauteur 50, espacements de 25 entre les boutons et 50 avec les bords du container +25 devant quitter
	menu_root->add(menu_root_inside, (Alignment::CENTERY | Alignment::CENTERX));
	Texture menu_inside_background(300, 500);
	menu_inside_background.fill(_octopus->getRenderer(), Color::GREEN);
	menu_root_inside->setBackground(menu_inside_background);

	Button* button_1 = new Button(150, 50);
	menu_root_inside->add(button_1, Alignment::CENTERX);
	button_1->setPositionY(50);
	button_1->setText("Play");
	button_1->setTextColor(Color::BLUE);
	button_1->setTextAlignment(Alignment::CENTERX | Alignment::CENTERY);
	button_1->Clickable::setCallback(new EventCallback(navigationLambda, menu_1));

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
	tt->setText("Text exemple");
	menu_root->add(tt, Alignment::RIGHT | Alignment::CENTERY);
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
	cout << "Main loop !" << endl;
	while (_running)
	{
		/* TODO: BEGIN FRAME */
		_timeService->beginFrame();
		/* TODO: PROCESS USER INPUT */
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
			{
				//Quit the program
				stop();
			}
			ev = SDLEvents::createEventFromSDLEvent(&e);
			if(ev)
				_eventService->dispatch(ev);
		}
		//SDL_Delay(1);

		/* Update */
		_timeService->update();
		_octopus->update();
		/* TODO: UPDATE */
		this->update();

		/*

		cout << "Number of active game objects: " << getNbActiveGObjects() << endl;
		*/

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
void Game::start()
{
	beginTurn();
}
void Game::beginTurn()
{
	LOGINFO << "Begining turn of " << _players.at(_player_turn)->getName() << endl;
	UI->addAction(Action(Callback(&Game::stop, this), "Quit"));
	UI->addAction(Action(Callback(&Game::endTurn, this), "I'm done"));
	_players.at(_player_turn)->beginTurn();
	_grid->beginTurn();
}
void Game::endTurn(void* )
{
	_players.at(_player_turn)->endTurn();
	_turn += _player_turn;
	_player_turn = _player_turn == 0 ? 1 : 0;
	UI->clear();
	beginTurn();
}