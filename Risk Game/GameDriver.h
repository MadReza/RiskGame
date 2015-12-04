#ifndef GAME_DRIVER_H
#define GAME_DRIVER_H

#include "BattleEngine\Player.h"
#include "Map\Map.h"
#include "Instantiation.h"
#include "BattleEngine\CardUtilities.h"
#include "Validation.h"
#include "UI\PlayerViewDecorator.h"
#include "UI\StatsObserver.h"
#include "Screen.h"

#include <iostream>
#include <stdio.h>
#include <set>
#include <vector>
#include <chrono>
#include <thread>
#include <typeinfo>

using namespace std;
using namespace std::chrono;

class GameDriver
{
public:
	static GameDriver* getInstance();	//TODO: Should probably set this to reference to not allow random delete the object
	~GameDriver();

	void startGame();
	std::thread startGameThread();	//Call this to initiate startGame on a new thread.

	// setters
	void setTotalPlayers(int n);
	void setPlayers(vector<Player*> p);
	void setSelectedMap(Map* m);

private:
	static GameDriver* instance;

	StatsObserver* statsObserver = nullptr;

	int totalPlayers;
	vector<Player*> players;
	vector<PlayerView*> playerViews;
	Map* selectedMap = nullptr;
	
	GameDriver();

	bool checkWinCondition();	//return true if one player left in the game, false otherwise.

	void playerAssignReinforcmentToCountries(Player* player);
	
	void log();

	void play();
	void reinforcePhase(Player* player);
	void attackPhase(Player* player);
	void fortifcationPhase(Player* player);
	void saveGame();
	void switchPlayerType(Player* player);

	void displayCountriesWithArmy(vector<Country*> countries);
};
#endif 