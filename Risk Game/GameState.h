#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "GameManager.h"

class GameManager;

class GameState
{
public:

	GameManager* game = nullptr;

	//Every Part will handleinput and Update all required fields THEN draw.

	virtual void handleInput() = 0;
	virtual void update(const float dt) = 0;
	virtual void draw(const float dt) = 0;
};
#endif // !GAME_STATE_H