#ifndef INSTANTIATION_H
#define INSTANTIATION_H

#include "Directory.h"
#include "Map\Map.h"
#include "Map\UtilityMap.h"

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

	int GetTotalPlayers() const;
	vector<Player*> GetPlayers() const;
	Map *GetMap() const;
	bool GetIsNewGame() const;

private:
	vector<Player*> players;
	int totalPlayers;
	int totalHumanPlayers;
	int totalCompPlayers;
	string mapPath;
	Map *map;
	bool newGame;

	void Intro();
	void GameSelection();
	void AssignCountriesToPlayer();
	void PlayerInfo();
	void DisplayTitleScreen();
	int StartOrLoad();
	void NewGame();
	void LoadGame();
	void CreateMap();
	void CreatePlayers();
	void MapSelection();

	void CreateHumanPlayers();
	void CreateCompPlayers();
	void RandomizePlayerOrder();
};

#endif