#pragma once
#include "GameBuilder.h"
#include "../Instantiation.h"

class GameBuilder;
class Instantiation;

class GameDirector {
private:
    GameBuilder* _builder;
public:
    GameDirector(GameBuilder* builder);
    Instantiation* getGame();
    void buildGame();
};



