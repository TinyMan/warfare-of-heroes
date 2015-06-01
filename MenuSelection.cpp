#include "MenuSelection.h"


MenuSelection::MenuSelection() : Panel()
{
	Archer* a = new Archer(-2,12);
	Knight* k = new Knight(-14,5);
	Mage* m = new Mage(0,3);

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

	choiceJ1 = new Button(75, 75);
	selection_top->add(choiceJ1);
	choiceJ1->setHover(false);
	choiceJ1->setPosition(110, 100);
	/*Texture t = (*ServiceLocator::getTextureManager())["obstacle_0"];
	choiceJ1->setBackground(t);
	choiceJ1->setHoverBackground(t);*/

	nameJ1 = new Label(150, 50, "J1", (*ServiceLocator::getFontManager())["LifeCraft"]);
	selection_top->add(nameJ1);
	nameJ1->setPositionX(325);
	nameJ1->setPositionY(110);

	choiceJ2 = new Button(75, 75);
	selection_top->add(choiceJ2);
	choiceJ2->setHover(false);
	choiceJ2->setPosition(1015, 100);
	/*Texture t2 = (*ServiceLocator::getTextureManager())["obstacle_1"];
	choiceJ2->setBackground(t2);
	choiceJ2->setHoverBackground(t2);*/

	nameJ2 = new Label(150, 50, "J2", (*ServiceLocator::getFontManager())["LifeCraft"]);
	selection_top->add(nameJ2);
	nameJ2->setPositionX(800);
	nameJ2->setPositionY(110);

	Button* button_selec_1 = new Button(150, 50);
	selection_top->add(button_selec_1);
	button_selec_1->setText("Pret");
	button_selec_1->setPadding(50);
	button_selec_1->setPositionY(100);
	button_selec_1->setPositionX(500);
	button_selec_1->setBgColor(Color::RED);
	button_selec_1->Clickable::setCallback(new EventCallback([=](Event*) {ready(); }));

	Panel* selection_bottom = new Panel(1200, 600);
	this->add(selection_bottom);
	selection_bottom->setBgColor(Color::BLUE);
	selection_bottom->setPosition(0, 200);

	Button* choice1 = new Button(125, 125);
	selection_bottom->add(choice1);
	choice1->setPosition(200, 100);
	choice1->Clickable::setCallback(new EventCallback([=](Event*) {selectClass(a); }));
	choice1->setHoverBackground((*ServiceLocator::getTextureManager())["icon_archer"]);
	choice1->setBackground((*ServiceLocator::getTextureManager())["icon_archer"]);

	Button* choice2 = choice1->clone();
	selection_bottom->add(choice2);
	choice2->setPosition(200 - 62, 100 + 125);
	choice2->Clickable::setCallback(new EventCallback([=](Event*) {selectClass(k); }));
	choice2->setBackground((*ServiceLocator::getTextureManager())["icon_knight"]);
	choice2->setHoverBackground((*ServiceLocator::getTextureManager())["icon_knight"]);

	Button* choice3 = choice1->clone();
	selection_bottom->add(choice3);
	choice3->setPosition(200 + 63, 100 + 125);
	choice3->Clickable::setCallback(new EventCallback([=](Event*) {selectClass(m); }));
	choice3->setBackground((*ServiceLocator::getTextureManager())["icon_mage"]);
	choice3->setHoverBackground((*ServiceLocator::getTextureManager())["icon_mage"]);

	Panel* spellInfos = new Panel(500, 400);
	this->add(spellInfos);
	spellInfos->setBgColor(Color::BLACK);
	spellInfos->setPosition(600, 250);

	nomClasse = new Label(150, 25, "Nom Classe", (*ServiceLocator::getFontManager())["LifeCraft"]);
	spellInfos->add(nomClasse);
	nomClasse->setPosition(25, 10);

	descrClasse = new Label(400, 35, "Description de la classe : bla bla bla bla bla bla bla", (*ServiceLocator::getFontManager())["LifeCraft"]);
	spellInfos->add(descrClasse);
	descrClasse->setPosition(15, 35);
	descrClasse->setTextSize(22);

	spell1 = new Button(75, 75);
	spellInfos->add(spell1);
	spell1->setPosition(50, 100);
	spell1->Clickable::setCallback(new EventCallback([=](Event*) {selectSpell(0); }));

	spell2 = new Button(75, 75);
	spellInfos->add(spell2);
	spell2->setPosition(50 + 100, 100);
	spell2->Clickable::setCallback(new EventCallback([=](Event*) {selectSpell(1); }));

	spell3 = new Button(75, 75);
	spellInfos->add(spell3);
	spell3->setPosition(50 + 100 + 100, 100);
	spell3->Clickable::setCallback(new EventCallback([=](Event*) {selectSpell(2); }));

	spell4 = new Button(75, 75);
	spellInfos->add(spell4);
	spell4->setPosition(50 + 100 + 100 + 100, 100);
	spell4->Clickable::setCallback(new EventCallback([=](Event*) {selectSpell(3); }));

	nomSpell = new Label(400, 50, "Nom Spell", (*ServiceLocator::getFontManager())["LifeCraft"]);
	spellInfos->add(nomSpell);
	nomSpell->setPosition(25, 175);

	descrSpell = new Label(500, 150, "Description du Spell : bla bla bla bla bla", (*ServiceLocator::getFontManager())["LifeCraft"]);
	spellInfos->add(descrSpell);
	descrSpell->setPosition(25, 205);
	descrSpell->setTextSize(22);
	descrSpell->setTextAlignment(Alignment::CENTERY | Alignment::LEFT);

	infos = new Label(400, 35, "Cost : X , Range : Y , inline / aoe", (*ServiceLocator::getFontManager())["LifeCraft"]);
	spellInfos->add(infos);
	infos->setPosition(25, 350);
	infos->setTextSize(22);
}


MenuSelection::~MenuSelection()
{
}

void MenuSelection::selectClass(Character* c) {
	if (c != _selected_class)
	{
		_selected_class = c;
		updateClass();
	}
}

void MenuSelection::selectSpell(int s) {
		_selected_spell_id = s;
		updateSpell();
}

void MenuSelection::updateClass() {
	nomClasse->setText(_selected_class->getName());
	int rang;
	if (_selected_class->getType() == "archer")
		rang = 1;
	else if (_selected_class->getType() == "knight")
		rang = 5;
	else
		rang = 9;

	spell1->setBackground((*ServiceLocator::getTextureManager())["icon_spell_"+to_string(rang)]);
	spell1->setHoverBackground((*ServiceLocator::getTextureManager())["icon_spell_" + to_string(rang)]);
	spell2->setBackground((*ServiceLocator::getTextureManager())["icon_spell_" + to_string(rang + 1)]);
	spell2->setHoverBackground((*ServiceLocator::getTextureManager())["icon_spell_" + to_string(rang+1)]);
	spell3->setBackground((*ServiceLocator::getTextureManager())["icon_spell_" + to_string(rang + 2)]);
	spell3->setHoverBackground((*ServiceLocator::getTextureManager())["icon_spell_" + to_string(rang + 2)]);
	spell4->setBackground((*ServiceLocator::getTextureManager())["icon_spell_" + to_string(rang + 3)]);
	spell4->setHoverBackground((*ServiceLocator::getTextureManager())["icon_spell_" + to_string(rang + 3)]);

	selectSpell(0);
}

void MenuSelection::updateSpell() {
	nomSpell->setText(_selected_class->getSpell(_selected_spell_id)->getName());
	descrSpell->setText(_selected_class->getSpell(_selected_spell_id)->getDescription());
	infos->setText("Cost : " + to_string(_selected_class->getSpell(_selected_spell_id)->getCPCost()) + ", Range : " + to_string(_selected_class->getSpell(_selected_spell_id)->getMaxScope()));
}


void MenuSelection::updateIcone1() {
	choiceJ1->setBackground((*ServiceLocator::getTextureManager())["icon_" + j1->getType()]);
	choiceJ1->setHoverBackground((*ServiceLocator::getTextureManager())["icon_" + j1->getType()]);
	nameJ1->setText(j1->getName());
}


void MenuSelection::updateIcone2() {
	choiceJ2->setBackground((*ServiceLocator::getTextureManager())["icon_" + j2->getType()]);
	choiceJ2->setHoverBackground((*ServiceLocator::getTextureManager())["icon_" + j2->getType()]);
	nameJ2->setText(j2->getName());
}


void MenuSelection::ready() {
	if (j1 == nullptr)
	{
		j1 = _selected_class;
		updateIcone1();
	}
	else if (j2 == nullptr)
	{
		j2 = _selected_class;
		updateIcone2();
		// gameStart(j1,j2);
	}
}