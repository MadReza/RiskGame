#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "GameManager.h"
#include "GameState.h"
#include "GUI.h"
#include <SFML/Graphics.hpp>

class MainMenu : public GameState
{
public:
	MainMenu(GameManager* game);
	~MainMenu();

	void handleInput();
	void update(const float dt);
	void draw(const float dt);

private:

};

#endif