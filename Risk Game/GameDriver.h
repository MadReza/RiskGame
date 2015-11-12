#ifndef GAME_DRIVER_H
#define GAME_DRIVER_H

#include "BattleEngine\Player.h"
#include "Map\Map.h"

class GameDriver
{
public:
	static GameDriver GetInstance();
	~GameDriver();

private:
	static GameDriver instance;

	int totalPlayers;
	vector<Player*> players;
	Map* selectedMap = nullptr;
	
	GameDriver();

	bool CheckWinCondition();	//return true if one player left in the game, false otherwise.

	void PlayerAssignReinforcmentToCountries(Player* player);
	
	void Play();
	void ReinforcePhase(Player* player);
	void AttackPhase(Player* player);
	void FortifcationPhase(Player* player);
	
	void PlayerAssignsAttacks();

};
#endif 