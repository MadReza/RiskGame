#include "GameManager.h"

void GameManager::gameLoop()
{
	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Time elapsed{ clock.restart() };
		float dt{ elapsed.asSeconds() };

		if (peekState() == nullptr)
			continue;
		peekState()->handInput();
		peekState()->update(dt);

		window.clear(sf::Color::Black);
		peekState()->draw(dt);
		window.display();
	}
}

GameManager::GameManager(string gameTitle)
{
	window.create(sf::VideoMode(800, 600), gameTitle);
	window.setFramerateLimit(60);	//TODO:: As we have delta time we can probably remove this after some testing.
}

GameManager::~GameManager()
{
	while (!gameState.empty())
	{
		popState();	//Delete happens in pop.
	}
}

void GameManager::pushState(GameState* state)
{
	gameState.push(state);
}

void GameManager::popState()
{
	delete gameState.top();
	gameState.pop();
}

void GameManager::changeState(GameState* state)
{
	if (!gameState.empty())
	{
		popState();
	}
	pushState(state);
}

GameState* GameManager::peekState()
{
	if (gameState.empty())
	{
		return nullptr;
	}
	return gameState.top();
}