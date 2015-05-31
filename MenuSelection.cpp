#include "MenuSelection.h"


MenuSelection::MenuSelection() : Panel()
{
	Panel* selection_top = new Panel(1200, 200);
	this->add(selection_top, (Alignment::TOP | Alignment::LEFT));
	selection_top->setBgColor(Color::WHITE);

	Label* j1 = new Label(150, 50, "Joueur 1 :", (*ServiceLocator::getFontManager())["LifeCraft"]);
	selection_top->add(j1);
	j1->setPositionX(100);
	j1->setPositionY(50);

	Label* j2 = new Label(150, 50, "Joueur 2 :", (*ServiceLocator::getFontManager())["LifeCraft"]);
	selection_top->add(j2);
	j2->setPositionX(1000);
	j2->setPositionY(50);

	Button* choiceJ1 = new Button(75, 75);
	selection_top->add(choiceJ1);
	choiceJ1->setHover(false);
	choiceJ1->setPosition(110, 100);

	Label* nameJ1 = new Label(150, 50, "Nom ici", (*ServiceLocator::getFontManager())["LifeCraft"]);
	selection_top->add(nameJ1);
	nameJ1->setPositionX(325);
	nameJ1->setPositionY(110);

	Button* choiceJ2 = new Button(75, 75);
	selection_top->add(choiceJ2);
	choiceJ2->setHover(false);
	choiceJ2->setPosition(1015, 100);

	Label* nameJ2 = new Label(150, 50, "Nom ici", (*ServiceLocator::getFontManager())["LifeCraft"]);
	selection_top->add(nameJ2);
	nameJ2->setPositionX(800);
	nameJ2->setPositionY(110);

	Button* button_selec_1 = new Button(150, 50);
	selection_top->add(button_selec_1);
	button_selec_1->setText("Pret");
	button_selec_1->setPadding(50);
	button_selec_1->setPositionY(100);
	button_selec_1->setPositionX(500);

	Panel* selection_bottom = new Panel(1200, 600);
	this->add(selection_bottom);
	selection_bottom->setBgColor(Color::BLUE);
	selection_bottom->setPosition(0, 200);

	Button* choice1 = new Button(125, 125);
	selection_bottom->add(choice1);
	choice1->setPosition(200, 100);

	Button* choice2 = new Button(125, 125);
	selection_bottom->add(choice2);
	choice2->setPosition(200 - 62, 100 + 125);

	Button* choice3 = new Button(125, 125);
	selection_bottom->add(choice3);
	choice3->setPosition(200 + 63, 100 + 125);

	Panel* spellInfos = new Panel(500, 300);
	this->add(spellInfos);
	spellInfos->setBgColor(Color::BLACK);
	spellInfos->setPosition(600, 275);

	Label* nomClasse = new Label(150, 25, "Nom Classe", (*ServiceLocator::getFontManager())["LifeCraft"]);
	spellInfos->add(nomClasse);
	nomClasse->setPosition(25, 10);

	Label* descrClasse = new Label(400, 35, "Description de la classe : bla bla bla bla bla bla bla", (*ServiceLocator::getFontManager())["LifeCraft"]);
	spellInfos->add(descrClasse);
	descrClasse->setPosition(15, 35);
	descrClasse->setTextSize(22);

	Button* spell1 = new Button(75, 75);
	spellInfos->add(spell1);
	spell1->setPosition(50, 100);

	Button* spell2 = new Button(75, 75);
	spellInfos->add(spell2);
	spell2->setPosition(50 + 100, 100);

	Button* spell3 = new Button(75, 75);
	spellInfos->add(spell3);
	spell3->setPosition(50 + 100 + 100, 100);

	Button* spell4 = new Button(75, 75);
	spellInfos->add(spell4);
	spell4->setPosition(50 + 100 + 100 + 100, 100);

	Label* nomSpell = new Label(150, 50, "Nom Spell", (*ServiceLocator::getFontManager())["LifeCraft"]);
	spellInfos->add(nomSpell);
	nomSpell->setPosition(25, 175);

	Label* descrSpell = new Label(400, 35, "Description du Spell : bla bla bla bla bla", (*ServiceLocator::getFontManager())["LifeCraft"]);
	spellInfos->add(descrSpell);
	descrSpell->setPosition(25, 205);
	descrSpell->setTextSize(22);

	Label* infos = new Label(400, 35, "Cost : X , Range : Y , inline / aoe", (*ServiceLocator::getFontManager())["LifeCraft"]);
	spellInfos->add(infos);
	infos->setPosition(25, 235);
	infos->setTextSize(22);
}


MenuSelection::~MenuSelection()
{
}
