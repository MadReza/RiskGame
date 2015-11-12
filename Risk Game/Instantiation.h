#ifndef INSTANTIATION_H
#define INSTANTIATION_H

#include "Directory.h"
#include "Map\Map.h"
#include "Map\UtilityMap.h"
#include "Map\MapCreator.h"

#include <iostream>
#include <string>
#include <random>

using std::string;
using std::cin;
using std::cout;
using std::endl;

class Instantiation
{
public:
	Instantiation();
	~Instantiation();

	int getTotalPlayers() const;
	vector<Player*> getPlayers() const;
	Map *getMap() const;
	bool getIsNewGame() const;

private:
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
};

#endif