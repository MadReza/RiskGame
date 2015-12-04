#ifndef INSTANTIATION_H
#define INSTANTIATION_H

#include "Directory.h"
#include "Map\Map.h"
#include "Map\UtilityMap.h"
#include "Map\MapCreator.h"
#include "GameDriver.h"
#include "GameState\GameBuilder.h"
#include "GameState\GameDirector.h"
#include "libs/PugiXML/pugixml.hpp"
#include "Validation.h"
#include "BattleEngine\Agressive.h"
#include "BattleEngine\Defensive.h"
#include "BattleEngine\Random.h"
#include "Screen.h"

#include <iostream>
#include <string>
#include <random>

using std::string;
using std::cin;
using std::cout;
using std::endl;
using namespace risk;

class GameDriver;

class Instantiation
{
public:
	Instantiation();
	~Instantiation();

	int getTotalPlayers();
	vector<Player*> getPlayers();
	void setPlayers(vector<Player*> players);
	Map *getMap();
	bool getIsNewGame();
	GameDriver *getGameDriver();

	void setIsNewGame(bool newGame);
	void setMap(Map* m);
	void setMapPath(string path);
	int getTotalHumanPlayers();
	void setTotalHumanPlayers(int n);
	int getTotalCompPlayers();
	void setTotalCompPlayers(int n);
	void setTotalPlayers(int n);
	
	void setMapFilename(string filename);

	void displayTitleScreen();
	void gameSelection();

private:
	GameDriver* _game;
	vector<Player*> players;
	int totalPlayers;
	int totalHumanPlayers;
	int totalCompPlayers;
	string mapPath;
	Map *map;
	string mapFilename;
	bool isNewGame;

	void intro();
	void assignCountriesToPlayer();
	void playerInfo();
	int startOrLoad();
	void newGame();
	void loadGame();
	void createMap();
	void createPlayers();
	void mapSelection();

	void createHumanPlayers();
	void createCompPlayers();
	void randomizePlayerOrder();
	int  chooseCompStrategy(int computerNumber);
};

#endif