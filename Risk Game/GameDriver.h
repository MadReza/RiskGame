#ifndef GAME_DRIVER_H
#define GAME_DRIVER_H

#include "BattleEngine\Player.h"
#include "Map\Map.h"

class GameDriver
{
public:
	static GameDriver getInstance();
	~GameDriver();

private:
	static GameDriver instance;

	int totalPlayers;
	vector<Player*> players;
	Map* selectedMap = nullptr;
	
	GameDriver();

	bool checkWinCondition();	//return true if one player left in the game, false otherwise.

	void playerAssignReinforcmentToCountries(Player* player);
	
	void play();
	void reinforcePhase(Player* player);
	void attackPhase(Player* player);
	void fortifcationPhase(Player* player);
	
	void playerAssignsAttacks();

	void displayCountriesWithArmy(vector<Country*> countries);
};
#endif 