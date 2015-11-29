#include "MainMenu.h"


MainMenu::MainMenu(GameManager* game)
{
	this->game = game;
}

MainMenu::~MainMenu()
{
}

void MainMenu::handleInput()
{

}

void MainMenu::update(const float dt)
{

}

void MainMenu::draw(const float dt)
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	game->window.draw(shape);
	sf::Text poop{GUI::Text("poop")};
	//game->window.draw(poop);
}