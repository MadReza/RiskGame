#include "GameDriver.h"

GameDriver GameDriver::instance;

GameDriver GameDriver::getInstance()
{
	return instance;
}

GameDriver::GameDriver()
{
	gui.start();
	Instantiation start;
	totalPlayers = start.getTotalPlayers();
	players = start.getPlayers();
	selectedMap = start.getMap();
	
	play();
}

GameDriver::~GameDriver()
{
	for (int i = 0; i != players.size(); i++)		
	{		
		delete players[i];		
	}		
	delete selectedMap;
}

void GameDriver::play()
{
	while (!checkWinCondition())
	{
		for each (Player* player in players)
		{
			if (!player->getAlive())
				continue;
			reinforcePhase(player);
			attackPhase(player);
			fortifcationPhase(player);
		}
	}
}

bool GameDriver::checkWinCondition()
{
	int playersAlive = 0;
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->getAlive())
			playersAlive++;

		if (playersAlive > 1)
			return false;
	}
	return true;
}

void GameDriver::reinforcePhase(Player* player)
{
	cout << "\n****Reinforcment Phase:: ****" << endl;
	playerAssignReinforcmentToCountries(player);
}

void GameDriver::playerAssignReinforcmentToCountries(Player* player)
{
	cout << "\tPlayer: " << player->getName() << " Adding Units to Countries." << endl;
	player->assignReinforcements();
}

void GameDriver::attackPhase(Player* player)
{
	cout << "\n****Attack Phase:: ****" << endl;
	playerAssignsAttacks();
	cout << "\tIf Won Allow, Movement to new country" << endl;
	system("pause");
	system("cls");
	//If won move to country X soldies.
}

void GameDriver::playerAssignsAttacks()
{
	cout << "\tGo through player countries. Allow attack adjacent country." << endl;
}

void GameDriver::fortifcationPhase(Player* player)
{
	cout << "\n****Fortification Phase:: ****" << endl;
	cout << "\tFor all countries, allow player to Move Army from one country to adjacent country to fortify" << endl;

	vector<Country*> playerCountries = player->getCountries();
	int selectionFrom{ -2 };
	int selectionTo{ -2 };
	int armyTransfer{ 0 };

	if (playerCountries.size() <= 1)
	{
		cout << "Sorry, you need to have more than 1 country to be able to fority." << endl;
		system("pause");
		return;
	}

	while (true)
	{
		displayCountriesWithArmy(playerCountries);

		cout << "Type -1 to End fortification at any time." << endl;

		do{
			cout << "Select Which country to transfer from(must have more than 1 army): ";
			cin >> selectionFrom;

			if (selectionFrom == -1)	//End Fortification
			{
				cout << "Fortification Done." << endl;
				system("pause");
				system("cls");
				return;
			}

		} while (selectionFrom < 0 || playerCountries[selectionFrom]->getNumArmies() <= 1);

		displayCountriesWithArmy(playerCountries);
		cout << "Type -1 to End fortification at any time." << endl;

		do
		{
			cout << "Select Which country to transfer To ";
			cin >> selectionTo;

			if (selectionFrom == -1)	//End Fortification
			{
				cout << "Fortification Done." << endl;
				system("pause");
				system("cls");
				return;
			}
		} while (selectionFrom == selectionTo);

		selectedMap->resetFortificationDFS();
		if (selectedMap->connectedDFS(player, playerCountries[selectionFrom], playerCountries[selectionTo]))
		{
			selectedMap->resetFortificationDFS();
			do
			{
				cout << "Path Found between " << playerCountries[selectionFrom]->getName() << " to " << playerCountries[selectionTo]->getName() << endl;
				cout << playerCountries[selectionFrom]->getName() << " has army size of " << playerCountries[selectionFrom]->getNumArmies() << endl;
				cout << playerCountries[selectionTo]->getName() << " has army size of " << playerCountries[selectionTo]->getNumArmies() << endl;

				cout << "How many army would you like to transfer from " << playerCountries[selectionFrom]->getName() << " between (0 to " << playerCountries[selectionFrom]->getNumArmies() - 1 << endl;
				cin >> armyTransfer;
			} while (armyTransfer < 0 || armyTransfer >= playerCountries[selectionFrom]->getNumArmies());

			if (armyTransfer != 0)
			{
				playerCountries[selectionFrom]->addArmies(-armyTransfer);
				playerCountries[selectionTo]->addArmies(armyTransfer);

				cout << "Transfer Succeeded" << endl;
				cout << playerCountries[selectionFrom]->getName() << " has army size of " << playerCountries[selectionFrom]->getNumArmies() << endl;
				cout << playerCountries[selectionTo]->getName() << " has army size of " << playerCountries[selectionTo]->getNumArmies() << endl;
				system("pause");
				return;
			}
		}
		else
		{
			cout << "Did not Find a connection between countries, try again." << endl;
		}
	}
}

void GameDriver::displayCountriesWithArmy(vector<Country*> countries)
{
	for (int i = 0; i < countries.size(); i++)
	{
		cout << i << ": " << countries[i]->getName() << " army: " << countries[i]->getNumArmies() << endl;
	}
}