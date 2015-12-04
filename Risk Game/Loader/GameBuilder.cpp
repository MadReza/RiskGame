#include "GameBuilder.h"



GameBuilder::GameBuilder(string serializedGame) {
    _serializedGame = serializedGame;
    //_game = new Instantiation();
}

void GameBuilder::buildMap() {
    //TODO: get the map from the serialized string (not the purpose of this assignment)
   // Map* m = new Map();
    //_game->setMap(m);
}

void GameBuilder::buildPlayers() {
    //TODO: get the players from the serialized string (not the purpose of this assignment)
    vector<Player*> players;
    //_game->setPlayers(players);
}

Instantiation* GameBuilder::getGame() {
    return _game;
}
