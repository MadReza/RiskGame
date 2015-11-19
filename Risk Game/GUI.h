#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>

using sf::RenderWindow;

class Gui
{
public:
	void start();

private:
	RenderWindow *window;
};

#endif // !GUI_H
