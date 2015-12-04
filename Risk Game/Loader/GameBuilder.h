#pragma once
#include <string>
#include <vector>
#include "../Map/Map.h"
#include "../Instantiation.h"
#include "../BattleEngine/Player.h"


class GameBuilder {
private:
    string _serializedGame;
    Instantiation* _game;
public:
    GameBuilder(string serializedGame);
    void buildMap();
    void buildPlayers();
    Instantiation* getGame();
};


