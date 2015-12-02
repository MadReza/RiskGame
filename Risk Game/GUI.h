#ifndef GUI_H
#define GUI_H

#define ARIAL "..\\Resources\\arial.ttf"

#include <SFML/Graphics.hpp>
#include <string>

using std::string;

static class GUI
{
public:
	static sf::Text GUI::Text(string msg, string fontName = ARIAL, int fontSize = 12, sf::Color color = sf::Color::Red);
private:
};

#endif // !GUI_H
