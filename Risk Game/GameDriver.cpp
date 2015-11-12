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

void GameDriver::AssignPlayOrder()
{
	cout << "Randomize the order in a way that no 2 turns same players goes first." << endl;
}

void GameDriver::ReinforcePhase(Player* player)
{
	cout << "****Reinforcment Phase:: ****" << endl;
	AssignReinforcmentToPlayers();
	PlayerAssignReinforcmentToCountries();
}

void GameDriver::AssignReinforcmentToPlayers()
{
	cout << "\tAdd units to each player depending on their current status." << endl;
}

void GameDriver::PlayerAssignReinforcmentToCountries()
{
	cout << "\tPlayer Adding Units to Countries." << endl;
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
}