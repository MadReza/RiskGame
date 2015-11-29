#ifndef GUIold_H
#define GUIold_H

#include <SFML/Graphics.hpp>
#include <string>

using sf::RenderWindow;
using sf::Font;
using std::string;

class GUIold
{
public:
	void start();

private:
	RenderWindow *window;
	Font *font;

	sf::Text Text(string msg);
};

#endif // !GUIold_H
