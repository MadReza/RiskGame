#include "GUI.h"

void Gui::start()
{
	window = new RenderWindow(sf::VideoMode(200, 200), "SFML works!");
	font = new Font();
	if (!font->loadFromFile("..\\Resources\\arial.ttf"))
	{
		// TODO Declare errors in here.
	}
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)	
				window->close();
		}

		window->clear();
		window->draw(shape);
		window->draw(Text("poop"));
		window->display();
	}
}

sf::Text Gui::Text(string msg)
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
