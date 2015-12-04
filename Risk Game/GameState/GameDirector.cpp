#include "GameDirector.h"

GameDirector::GameDirector(GameBuilder* builder) {
    _builder = builder;
}

Instantiation* GameDirector::getGame() {
    return _builder->getGame();
}

void GameDirector::buildGame() {
    _builder->buildMap();
    _builder->buildPlayers();
}
