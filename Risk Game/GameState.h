#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "GameDriver.h"

class GameState
{
public:

	GameDriver* game;

	//Every Part will handleinput and Update all required fields THEN draw.

	virtual void handInput() = 0;
	virtual void update(const float dt) = 0;
	virtual void draw(const float dt) = 0;
};
#endif // !GAME_STATE_H