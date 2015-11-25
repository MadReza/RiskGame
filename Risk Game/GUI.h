#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <string>

using sf::RenderWindow;
using sf::Font;
using std::string;

class Gui
{
public:
	void start();

private:
	RenderWindow *window;
	Font *font;

	sf::Text Text(string msg);
};

#endif // !GUI_H
