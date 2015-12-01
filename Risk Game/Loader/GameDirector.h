#pragma once
#include "GameBuilder.h"
#include "../Instantiation.h"

class GameDirector {
private:
    GameBuilder* _builder;
public:
    GameDirector(GameBuilder* builder);
    Instantiation* getGame();
    void buildGame();
};



