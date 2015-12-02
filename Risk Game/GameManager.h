#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "GameState.h"

#include <stack>
#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

using std::string; 

class GameState;

class GameManager
{
public:
	//Stack of game state because of Pause and other neat states requiring to temporaraly move from the active state.
	std::stack<GameState*> gameState;
	sf::RenderWindow window;

	GameManager(string gameTitle);
	~GameManager();

	void pushState(GameState* state);
	void popState();
	void changeState(GameState* state);
	GameState* peekState();

	void gameLoop();	
};

#endif // !GAME_MANAGER_H