#include "MainMenu.h"


MainMenu::MainMenu(GameManager* game)
{
	this->game = game;
	//Center the View to the Main View.
	sf::Vector2f pos = sf::Vector2f(game->window.getSize());
	view.setSize(pos);
	pos *= 0.5f;
	view.setCenter(pos);

	uploadResources();	
}

MainMenu::~MainMenu()
{
}

void MainMenu::uploadResources()
{
	font = new sf::Font();
	if (!font->loadFromFile("..\\Resources\\arial.ttf"))
	{
		// TODO Declare errors in here.
	}
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
			view.setSize(event.size.width, event.size.height);	//TODO: Fix as image goes out of view.
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
	game->window.draw(text("poop"));
}


void MainMenu::startGame()
{

}

void MainMenu::loadGame()
{

}

void MainMenu::map()
{

}

sf::Text MainMenu::text(string msg)
{
	sf::Text text;

	// select the font
	text.setFont(*font); // font is a sf::Font

	// set the string to display
	text.setString(msg);

	// set the character size
	text.setCharacterSize(24); // in pixels, not points!

	// set the color
	text.setColor(sf::Color::Red);

	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	// inside the main loop, between window.clear() and window.display()
	return text;
}
