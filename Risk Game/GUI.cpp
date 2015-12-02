#include "GUI.h"

sf::Text GUI::Text(string msg, string fontName, int fontSize, sf::Color color)
{
	sf::Text text;
	sf::Font font;

	if (!font.loadFromFile(fontName))
	{
		// TODO Declare errors in here.
	}

	// select the font
	text.setFont(font); 

	// set the string to display
	text.setString(msg);

	// set the character size
	text.setCharacterSize(24); // in pixels, not points!

	// set the color
	text.setColor(color);

	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	// inside the main loop, between window.clear() and window.display()
	return text;
}