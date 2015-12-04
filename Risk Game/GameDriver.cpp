#include "GameDriver.h"


GameDriver* GameDriver::instance = 0;

GameDriver* GameDriver::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GameDriver();
	}
	return instance;
}

GameDriver::GameDriver()
{
	
}

GameDriver::~GameDriver()
{
	for (int i = 0; i != players.size(); i++)		
	{		
		delete players[i];		
	}		
	delete selectedMap;
}

void GameDriver::startGame()
{
	Instantiation* start = new Instantiation();	//Initializes all components then sends to GameDriver.
	start->displayTitleScreen();
	start->gameSelection();
	
	statsObserver = new StatsObserver(players, selectedMap->countCountries());
	statsObserver->display();

	log();
	play();
}

std::thread GameDriver::startGameThread() {
	return std::thread([=] { startGame(); });
}

void GameDriver::log()
{
	risk::clsGame();
	cout << "****Logging:: ****" << endl << endl;

	char selection;

	for each (Player* player in players)
	{
		cout << "For player: " << player->getName() << ": " << endl;
		cout << endl;

		do
		{
			cout << "\tWould you like to log every Phase(y,n): ";
			cin >> selection;
		} while (!std::validYesNo(selection));

		if (selection == 'y' || selection == 'Y')
		{
			PlayerView *pV = new PlayerView(*player);
			pV->logAllPhase(true);
			playerViews.push_back(pV);
			continue;
		}

		cout << endl;
		selection = 'z';	//Just reset
		PlayerView *pV = nullptr;

		do
		{
			cout << "\tWould you like to log Attack Phase: ";
			cin >> selection;
		} while (!std::validYesNo(selection));

		if (selection == 'y' || selection == 'Y')
		{
			if (pV == nullptr)
				pV = new PlayerView(*player);
			pV->logOnlyPhase(new Phase(Phase::Attack));
		}

		cout << endl;
		selection = 'z';	//Just reset

		do
		{
			cout << "\tWould you like to log Reinforce Phase: ";
			cin >> selection;
		} while (!std::validYesNo(selection));

		if (selection == 'y' || selection == 'Y')
		{
			if (pV == nullptr)
				pV = new PlayerView(*player);
			pV->logOnlyPhase(new Phase(Phase::Reinforce));
		}

		cout << endl;
		selection = 'z';	//Just reset

		do
		{
			cout << "\tWould you like to log Fortification Phase: ";
			cin >> selection;
		} while (!std::validYesNo(selection));

		if (selection == 'y' || selection == 'Y')
		{
			if (pV == nullptr)
				pV = new PlayerView(*player);
			pV->logOnlyPhase(new Phase(Phase::Fortification));
		}

		if (pV != nullptr)
		{
			playerViews.push_back(pV);
		}

	}
}

void GameDriver::play()
{
	while (!checkWinCondition())
	{
		for each (Player* player in players)
		{
			if (!player->getAlive())
				continue;
			saveGame();
			switchPlayerType(player);
			reinforcePhase(player);
			attackPhase(player);
			fortifcationPhase(player);
		}
	}
}

bool GameDriver::checkWinCondition()
{
	int playersAlive = 0;
	for (int i = 0; i < (int)players.size(); i++)
	{
		if (players[i]->getAlive())
			playersAlive++;

		if (playersAlive > 1)
			return false;
	}
	return true;
}

void GameDriver::switchPlayerType(Player* player){
	risk::clsGame();
	
	cout << "||-=-=-=-=-=-=-=-=||" << endl;
	cout << "||PLAYER SWTICHER!||" << endl;
	cout << "||-=-=-=-=-=-=-=-=||" << endl << endl;
	cout << "Currently you are : ";
	if (player->isHuman())
		cout << "A human";
	else{
		//cout << "A Computer with strategy of " << typeid(player->getPlayerStrategy()); //LAURENDY FIX THIS, what type of strategy
		cout << "A Computer with strategy of: " << player->getPlayerStrategy()->getStrategyName() << ".";
		
	}
	cout << endl;

	char answer;

	cout << "Would you like to switch player type? y/n > ";
	cin >> answer;

	while (!std::validYesNo(answer)){
		cout << "Try again > ";
		cin >> answer;
	}

	if (answer == 'N' || answer == 'n')
		return;

	int type;
	cout << endl << "What would you like to switch to? ";
	cout << "0: Human" << endl;
	cout << "1: Computer Agressive" << endl;
	cout << "2: Computer Defensive" << endl;
	cout << "3: Computer Random" << endl;
	cout << "> ";

	while (!std::validInteger(type, 0, 3)){ cout << "Try again > "; }

	switch (type){
		case 0 :
			player->setType(Player::Human);
			return;
		case 1 :
			player->setType(Player::Computer);
			player->setPlayerStrategy(new Agressive());
			return;
		case 2 : 
			player->setType(Player::Computer);
			player->setPlayerStrategy(new Defensive());
			return;
		case 3 :
			player->setType(Player::Computer);
			player->setPlayerStrategy(new Random());
			return;
	}
}
void GameDriver::reinforcePhase(Player* player)
{
	risk::clsGame(); 
	player->currentPhase = Phase::Reinforce;
	cout << "****Reinforcment Phase:: ****" << endl << endl;
	playerAssignReinforcmentToCountries(player);
}

void GameDriver::playerAssignReinforcmentToCountries(Player* player)
{
	cout << "\tPlayer: " << player->getName() << " Adding Units to Countries." << endl;
	player->resetRoundVariables();
	player->assignReinforcements();
}

void GameDriver::attackPhase(Player* player)
{
	risk::clsGame();
	player->currentPhase = Phase::Attack;
	cout << "****Attack Phase:: ****" << endl << endl << endl;
	char answer;

	PlayerViewDecorator *playerInfo = new CompletePlayerView(player);	//Displays decorator view
	delete playerInfo;

	do
	{
		if (player->isHuman())
		{
			cout << "Would you like to attack a country (y,n): ";
			cin >> answer;

			if (answer == 'y' || answer == 'Y')
				player->assignAttack();
		}
		else
		{
			player->assignAttack();	//TODO: Does the computer only attack once ???
			break;
		}

		if (answer == 'y' || answer == 'Y')
			player->assignAttack();

	} while (answer != 'n' && answer != 'N'); 

	if (player->getTurnVictory())
	{
		player->setTurnVictory(false);
		CardUtilities::getVictoryCard(player);
	}

	risk::pause();
}

void GameDriver::fortifcationPhase(Player* player)
{
	risk::clsGame();
	player->currentPhase = Phase::Reinforce;
	risk::setCursorPosition(risk::COORD_INI_GAME_SCREEN); //LAURENDY 
	cout << "****Fortification Phase:: ****" << endl << endl;
	cout << "For all countries, allow player to Move Army from one country to adjacent country to fortify" << endl;

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

		cout  << endl << "Type -1 to End fortification at any time." << endl;

		do{
			cout << "Select Which country to transfer from(must have more than 1 army): ";
			while (!std::validInteger(selectionFrom, -1, playerCountries.size() - 1)){
				cout << endl << "Please select a country from the list... > ";  
			}
			if (selectionFrom == -1)	//End Fortification
			{
				cout << "Fortification Done." << endl;
				system("pause");
				system("cls");
				return;
			}
		}while (playerCountries[selectionFrom]->getNumArmies() <= 1);

		displayCountriesWithArmy(playerCountries);
		cout << endl << "Type -1 to End fortification at any time." << endl;

		do
		{
			cout << "Select Which country to transfer To> ";
			/*cin >> selectionTo;*/
			std::validInteger(selectionTo, 0, 0); //just tries to validate the cin >> selection

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

				cout << "How many army would you like to transfer from " << playerCountries[selectionFrom]->getName() << " between (0 to " << playerCountries[selectionFrom]->getNumArmies() - 1 << ")" <<  endl;
				/*cin >> armyTransfer;*/
			} while (!std::validInteger(armyTransfer, 0, playerCountries[selectionFrom]->getNumArmies() - 1)/*armyTransfer < 0 || armyTransfer >= playerCountries[selectionFrom]->getNumArmies()*/);

			if (armyTransfer != 0)
			{
				playerCountries[selectionFrom]->addArmies(-armyTransfer);
				playerCountries[selectionTo]->addArmies(armyTransfer);

				cout << endl << "Transfer Succeeded" << endl;
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
	for (int i = 0; i < (int)countries.size(); i++)
	{
		cout << i << ": " << countries[i]->getName() << " army: " << countries[i]->getNumArmies() << endl;
	}
}

void GameDriver::setTotalPlayers(int n)
{
	totalPlayers = n;
}
void GameDriver::setPlayers(vector<Player*> p)
{
	players = p;
}
void GameDriver::setSelectedMap(Map* m)
{
	selectedMap = m;
}

void GameDriver::saveGame()
{
	char choice;
	do{
		cout << "Would you like to save the game? y/n : ";
		cin >> choice;
	} while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

	if (choice == 'y' || choice == 'Y')
	{
		cout << "Type the save name: ";
		string saveName;
		cin >> saveName;

		pugi::xml_document doc;
		pugi::xml_node save = doc.append_child("save");
		pugi::xml_node map = save.append_child("map");
		
		//	ADD MAP NAME
		char* mapName = new char[(this->selectedMap->getFilename().length()) + 1];
		strcpy_s(mapName, (this->selectedMap->getFilename()).length() + 1, (this->selectedMap->getFilename()).c_str());
		map.append_child(pugi::node_pcdata).set_value(mapName);


		pugi::xml_node players = save.append_child("players");
		for (Player* player : this->players)
		{
			pugi::xml_node player_node = players.append_child("player");
			
			char* player_name = new char[(player->getName().length()) + 1];
			strcpy_s(player_name, (player->getName()).length() + 1, (player->getName()).c_str());

			player_node.append_attribute("name") = player_name;
			player_node.append_attribute("type") = (player->getType() == Player::Human) ? "human" : "computer";
			player_node.append_attribute("alive") = player->getAlive();
			//player_node.append_attribute("reinforcementTotal") = player->getReinforcementTotal();
			player_node.append_attribute("armiesTotal") = player->getArmiesTotal();
			player_node.append_attribute("battlesWonTotal") = player->getBattlesWonTotal();
			player_node.append_attribute("cardRedemptionsTotal") = player->getCardRedemptionsTotal();
			player_node.append_attribute("redeemThisTurn") = player->getRedeemThisTurn();
			player_node.append_attribute("turnVictory") = player->getTurnVictory();

			pugi::xml_node continents = player_node.append_child("continents");
			set<Continent*> player_continents;
			for (Country* country : player->getCountries())
			{
				player_continents.insert(country->getContinentObject());
			}
			vector<Continent*> map_continents = this->selectedMap->getMapVector();
			for (int i = 0; i < map_continents.size(); i++)
			{
				Continent* continent = map_continents[i];
				if (find(player_continents.begin(), player_continents.end(), continent) != player_continents.end()) // if continent is owned by player
				{
					pugi::xml_node continent_node = continents.append_child("continent");
					
					char* continent_name = new char[(continent->getContinentName().length()) + 1];
					strcpy_s(continent_name, (continent->getContinentName()).length() + 1, (continent->getContinentName()).c_str());

					continent_node.append_attribute("name") = continent_name;
					continent_node.append_attribute("index") = i;

					pugi::xml_node countries = continent_node.append_child("countries");
					vector<Country*> map_countries = continent->getContinentVector();
					for (int j = 0; j < map_countries.size(); j++)
					{
						Country* country = map_countries[j];
						if (country->getOwner() == player)
						{
							pugi::xml_node country_node = countries.append_child("country");
							
							char* country_name = new char[(country->getName().length()) + 1];
							strcpy_s(country_name, (country->getName()).length() + 1, (country->getName()).c_str());

							country_node.append_attribute("name") = country_name;
							country_node.append_attribute("index") = j;
							country_node.append_attribute("armies") = country->getNumArmies();
						}
					}
				}
			}
			pugi::xml_node cards = player_node.append_child("cards");
			vector<Card*>* player_cards = player->getCards();
			for (int i = 0; i < player_cards->size(); i++)
			{
				Card* card = player_cards->at(i);
				pugi::xml_node card_node = cards.append_child("card");

				if (card->getCardSuit() == CardType::Artillery)
					card_node.append_attribute("type") = "artillery";
				else if (card->getCardSuit() == CardType::Infantry)
					card_node.append_attribute("type") = "infantry";
				else
					card_node.append_attribute("type") = "cavalry";
			}
		}

		milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		string file = "GameSaves\\" + to_string(ms.count()) + ".save.xml";
		char* filename = new char[(file.length()) + 1];
		strcpy_s(filename, (file).length() + 1, (file).c_str());
		doc.save_file(filename);

		pugi::xml_document saves_xml;
		pugi::xml_parse_result result2 = saves_xml.load_file("GameSaves\\saves.xml");

		if (result2)
		{
			pugi::xml_node saves = saves_xml.child("saves");
			pugi::xml_node save_node = saves.append_child("save");

			char* name = new char[(saveName.length()) + 1];
			strcpy_s(name, (saveName).length() + 1, (saveName).c_str());

			char* id = new char[(to_string(ms.count()).length()) + 1];
			strcpy_s(id, (to_string(ms.count())).length() + 1, (to_string(ms.count())).c_str());

			string file = to_string(ms.count()) + ".save.xml";
			char* filename = new char[(file.length()) + 1];
			strcpy_s(filename, (file).length() + 1, (file).c_str());

			save_node.append_attribute("name") = name;
			save_node.append_attribute("id") = id;
			save_node.append_attribute("filename") = filename;

			saves_xml.save_file("GameSaves\\saves.backup.xml");
			// remove saves.xml
			if (!remove("GameSaves\\saves.xml") != 0)
			{
				perror("Error saving file");
				// rename file
				rename("GameSaves\\saves.backup.xml", "GameSaves\\saves.xml");
			}
		}
		else
		{
			//	SAVES FILE DID NOT LOAD CORRECTLY
			cout << "Game did not save correctly: " << result2.description() << "\n";
		}

		cout << "\nfile saved as " << filename << endl << endl;
		system("pause");
	}
}