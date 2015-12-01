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
	sf::Event event;

	while (game->window.pollEvent(event))	//Returns true while there is more events to process.
	{
		switch (event.type)
		{
			/* Close the window */
		case sf::Event::Closed:
		{
			game->window.close();
			break;
		}
			/* Resize the window */
		case sf::Event::Resized:
		{
			view.setSize(event.size.width, event.size.height);			
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::Escape) 
				game->window.close();
			break;
		}
		default: break;
		}
	}
}

void MainMenu::update(const float dt)
{

}

void MainMenu::draw(const float dt)
{
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	game->window.setView(view); //Change Camera to ours.
	game->window.clear(sf::Color::Black);
	game->window.draw(shape);
	sf::Text poop{GUI::Text("poop")};
	//game->window.draw(poop);
}