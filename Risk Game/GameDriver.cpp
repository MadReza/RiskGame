#include "GameDriver.h"
#include "Instantiation.h"
#include <iostream>

using namespace std;

GameDriver GameDriver::instance;

GameDriver GameDriver::GetInstance()
{
	return instance;
}

GameDriver::GameDriver()
{
	Instantiation start;
	totalPlayers = start.GetTotalPlayers();
	players = start.GetPlayers();
	selectedMap = start.GetMap();
	
	Play();
}

GameDriver::~GameDriver()
{
	//TODO : Clean up each player object.
	//TODO : Clean Up the map.
}

void GameDriver::Play()
{
	while (!CheckWinCondition())
	{
		for each (Player* player in players)
		{
			if (!player->GetAlive())
				continue;
			ReinforcePhase(player);
			AttackPhase(player);
			FortifcationPhase(player);
		}
	}
}

bool GameDriver::CheckWinCondition()
{
	int playersAlive = 0;
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->GetAlive())
			playersAlive++;

		if (playersAlive > 1)
			return false;
	}
	return true;
}

void GameDriver::ReinforcePhase(Player* player)
{
	cout << "****Reinforcment Phase:: ****" << endl;
	PlayerAssignReinforcmentToCountries(player);
}

void GameDriver::PlayerAssignReinforcmentToCountries(Player* player)
{
	cout << "\tPlayer: " << player->getName() << " Adding Units to Countries." << endl;
	player->AssignReinforcements();
}

void GameDriver::AttackPhase(Player* player)
{
	cout << "****Attack Phase:: ****" << endl;
	PlayerAssignsAttacks();
	cout << "\tIf Won Allow, Movement to new country" << endl;
	//If won move to country X soldies.
}

void GameDriver::PlayerAssignsAttacks()
{
	cout << "\tGo through player countries. Allow attack adjacent country." << endl;
}

void GameDriver::FortifcationPhase(Player* player)
{
	cout << "****Fortification Phase:: ****" << endl;
	cout << "\tFor all countries, allow player to Move Army from one country to adjacent country to fortify" << endl;

	//TODO
	//Check he has more than 1 country
	//Then call DFS get true or false for connection
	//if connected
	//Call player transfer
	//else notify and let player choose again.
	//until player ends turn.	
}