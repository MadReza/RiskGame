#ifndef INSTANTIATION_H
#define INSTANTIATION_H

#include "Directory.h"
#include "Map\Map.h"
#include "Map\UtilityMap.h"
#include "Map\MapCreator.h"
#include "GameDriver.h"
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

class GameDriver;

class Instantiation
{
public:
	Instantiation();
	~Instantiation();

	int getTotalPlayers() const;
	vector<Player*> getPlayers() const;
	Map *getMap() const;
	bool getIsNewGame() const;
	GameDriver *getGameDriver() const;

private:
	GameDriver* _game;
	vector<Player*> players;
	int totalPlayers;
	int totalHumanPlayers;
	int totalCompPlayers;
	string mapPath;
	Map *map;
	bool isNewGame;

	void intro();
	void gameSelection();
	void assignCountriesToPlayer();
	void playerInfo();
	void displayTitleScreen();
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