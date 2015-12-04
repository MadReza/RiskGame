#pragma once
#include <string>
#include <vector>
#include "../libs/PugiXML/pugixml.hpp"
#include "../Map/Map.h"
#include "../Instantiation.h"
#include "../BattleEngine/Player.h"
#include "../Map/UtilityMap.h"

using namespace std;

class Instantiation;

class GameBuilder {
private:
    char* _filename;
	Instantiation* _game;

public:
    GameBuilder(char* filename);
    void buildMap();
    void buildPlayers();
    Instantiation* getGame();
};


