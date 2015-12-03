#include "Instantiation.h"

Instantiation::Instantiation()
{
	displayTitleScreen();
	gameSelection();
}

Instantiation::~Instantiation()
{

}

void Instantiation::gameSelection()
{
	int selection(startOrLoad());
	switch (selection)
	{
	case 0:
		newGame();
		break;
	case 1:
		loadGame();
		break;
	case 2:
		createMap();
		break;
	default:
		throw new std::exception("Game Selection Incorrect");
		break;
	}
}

int Instantiation::getTotalPlayers() const
{
	return totalPlayers;
}

Map* Instantiation::getMap() const
{
	return map;
}

bool Instantiation::getIsNewGame() const
{
	return isNewGame;
}

void Instantiation::newGame()
{
	system("cls");
	isNewGame = true;
	mapSelection();
	createPlayers();
	randomizePlayerOrder();
	assignCountriesToPlayer();

	_game = GameDriver::getInstance();
	_game->setTotalPlayers(getTotalPlayers());
	_game->setPlayers(getPlayers());
	_game->setSelectedMap(getMap());
}

void Instantiation::loadGame()
{
	system("cls");
	this->isNewGame = false;
	// TODO @zack : Assign Continent bonus to players who own complete continents

	// LOAD THE SAVES.XML FILE
	string savesDir = "GameSaves/";
	string savesPath = savesDir + "saves.xml";
	char* source = new char[savesPath.length() + 1];
	strcpy_s(source, savesPath.length() + 1, savesPath.c_str());

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(source);

	if (result)
	{
		// DISPLAY MENU TO USER
		pugi::xml_node saves = doc.child("saves");
		cout << "Please select which save you would like to load:" << endl;
		int i = 0;
		vector<string> filenames;
		for (pugi::xml_node save = saves.child("save"); save; save = save.next_sibling("save"))
		{
			cout << i << " - " << save.attribute("name").value() << endl;
			filenames.push_back(save.attribute("filename").value());
			i++;
		}

		//	USER SELECTS THE SAVE FILE
		int choice;
		do
		{
			cout << "Your choice: ";
		} while (!std::validInteger(choice, 0, i - 1));

		// SAVE FILE GETTING LOADED
		char* filename = new char[(savesDir + filenames[choice]).length() + 1];
		strcpy_s(filename, (savesDir + filenames[choice]).length() + 1, (savesDir + filenames[choice]).c_str());

		pugi::xml_parse_result result = doc.load_file(filename);

		if (result)
		{
			// SAVE FILE LOADED CORRECTLY
			pugi::xml_node save = doc.child("save");
			
			//	GET THE MAP
			pugi::xml_node map = save.child("map");

			//	CREATE THE MAP
			string str(Directory::GetCurrentWorkingDirectory());
			const char* cd = str.c_str();
			string path = Directory::CombinePaths(2, cd, "Mapfiles");
			this->mapPath = path + "\\" + map.child_value();
			UtilityMap m(this->mapPath);
			this->map = m.getMapObject();

			// GET THE PLAYERS
			pugi::xml_node players = save.child("players");
			for (pugi::xml_node player = players.child("player"); player; player = player.next_sibling("player"))
			{
				//	CREATE THE PLAYER
				Player* p;

				Player::Type type;
				if (player.attribute("type").value() == "human") 
				{
					type = Player::Human;
					this->totalHumanPlayers++;
				}
				else 
				{
					type = Player::Computer;
					this->totalCompPlayers++;
				}

				string name = player.attribute("name").value();
				
				p = new Player(name, type);
				this->players.push_back(p);

				// INCREMENT THE NUMBER OF PLAYERS
				this->totalPlayers++;

				//	GET THE CONTINENTS
				pugi::xml_node continents = player.child("continents");
				for (pugi::xml_node continent = continents.child("continent"); continent; continent = continent.next_sibling("continent"))
				{
					int continent_index = continent.attribute("index").as_int();
					
					//	GET THE COUNTRIES
					vector<int> countries_indices;
					vector<int> armies;
					pugi::xml_node countries = continent.child("countries");
					for (pugi::xml_node country = countries.child("country"); country; country = country.next_sibling("country"))
					{
						countries_indices.push_back(country.attribute("index").as_int());
						armies.push_back(country.attribute("armies").as_int());
					}

					//	ASSIGN COUNTRIES TO PLAYER
					this->map->assignCountriesToPlayer(p, continent_index, countries_indices, armies);
				}
			}
		}
		else
		{
			//	SAVE FILE DID NOT LOAD CORRECTLY
			cout << "Save file did not load correctly." << endl;
			cout << "XML [" << source << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
			cout << "Error description: " << result.description() << "\n";
			cout << "Error offset: " << result.offset << " (error at [..." << (source + result.offset) << "]\n\n";
		}
	}
	else
	{
		//	SAVES LIST FILE DID NOT LOAD CORRECTLY
		cout << "Saves list file did not load correctly." << endl;
		cout << "XML [" << source << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
		cout << "Error description: " << result.description() << "\n";
		cout << "Error offset: " << result.offset << " (error at [..." << (source + result.offset) << "]\n\n";
	}

	//return;

	_game = GameDriver::getInstance();
	_game->setTotalPlayers(this->getTotalPlayers());
	_game->setPlayers(this->getPlayers());
	_game->setSelectedMap(this->getMap());

	/*
	TODO by @zack : load serialized game from file and build the game using the GameBuilder
	string serializedGame = "serialized-string-example";

	GameBuilder* builder = new GameBuilder(serializedGame);
	GameDirector* director = new GameDirector(builder);

	director->buildGame();

	_game = director->getGame();
	//*/
}

GameDriver* Instantiation::getGameDriver() const
{
	return _game;
}

void Instantiation::createMap()
{
	MapCreator mapCreator;
}

void Instantiation::createPlayers()
{	
	system("cls");
	do
	{
		cout << "Total amount of Players(2 to " << map->getMaxPlayers() << "): ";
		//OLD cin >> totalPlayers;
	} while (!std::validInteger(totalPlayers, 2, map->getMaxPlayers()) /*OLD totalPlayers <= 1 || totalPlayers > map->getMaxPlayers()*/);

	do
	{
		cout << "How many Human Players(0 to " << totalPlayers << "): ";
		//OLD cin >> totalHumanPlayers;
	} while (!std::validInteger(totalHumanPlayers, 0, totalPlayers) /*OLD totalHumanPlayers < 0 || totalHumanPlayers > totalPlayers*/);

	createHumanPlayers();
	createCompPlayers();
}

void Instantiation::createHumanPlayers()
{
	for (int i = 0; i < totalHumanPlayers; i++)
	{
		string name;
		cout << "Enter name for Player " << i+1 << ": ";
		cin >> name;
		players.push_back(new Player(name, Player::Human));
	}
}

void Instantiation::createCompPlayers()
{
	totalCompPlayers = totalPlayers - totalHumanPlayers;
	for (int i = 0; i < totalCompPlayers; i++)
	{
		string name("Comp ");
		name += (i+1);
		players.push_back(new Player(name, Player::Computer));
	}
}

void Instantiation::mapSelection()
{
	system("cls");
	string str(Directory::GetCurrentWorkingDirectory());
	const char* cd = str.c_str();
	string path = Directory::CombinePaths(2, cd, "Mapfiles");

	vector<string> maps(Directory::GetFilesNamesFrom(path));
	int size = maps.size();
	int selection = -1;
	do
	{
		for (int i = 0; i < size; i++)
		{
			cout << i << ": " << maps[i] << endl;
		}
		cout << "Select Map Number: ";			
		//OLD cin >> selection;
	} while (!std::validInteger(selection, 0, size - 1)/*OLD selection < 0 || selection >= size*/);

	mapPath = path + "\\" + maps[selection];
	UtilityMap m(mapPath);
	map = m.getMapObject();
	system("pause");
}

void Instantiation::assignCountriesToPlayer()
{
	map->distributePlayers(players);
}

int Instantiation::startOrLoad()
{
	int selection;
	cout << "Type 0: To Start a New Game" << endl;
	cout << "Type 1: To Load a Game" << endl;
	cout << "Type 2: To Create a Map" << endl;
	cout << "Selection: ";

	while (!std::validInteger(selection, 0, 2))
	{
		cout << "Only allowed options are 0, 1, 2: ";
	}
	return selection;
}

void Instantiation::displayTitleScreen()
{
	cout << "RRRRRRRRRRRRRRRRR   IIIIIIIIII   SSSSSSSSSSSSSSS KKKKKKKKK    KKKKKKK" << endl;
	cout << "R::::::::::::::::R  I::::::::I SS:::::::::::::::SK:::::::K    K:::::K" << endl;
	cout << "R::::::RRRRRR:::::R I::::::::IS:::::SSSSSS::::::SK:::::::K    K:::::K" << endl;
	cout << "RR:::::R     R:::::RII::::::IIS:::::S     SSSSSSSK:::::::K   K::::::K" << endl;
	cout << "  R::::R     R:::::R  I::::I  S:::::S            KK::::::K  K:::::KKK" << endl;
	cout << "  R::::R     R:::::R  I::::I  S:::::S              K:::::K K:::::K" << endl;
	cout << "  R::::RRRRRR:::::R   I::::I   S::::SSSS           K::::::K:::::K" << endl;
	cout << "  R:::::::::::::RR    I::::I    SS::::::SSSSS      K:::::::::::K" << endl;
	cout << "  R::::RRRRRR:::::R   I::::I      SSS::::::::SS    K:::::::::::K" << endl;
	cout << "  R::::R     R:::::R  I::::I         SSSSSS::::S   K::::::K:::::K" << endl;
	cout << "  R::::R     R:::::R  I::::I              S:::::S  K:::::K K:::::K" << endl;
	cout << "  R::::R     R:::::R  I::::I              S:::::SKK::::::K  K:::::KKK" << endl;
	cout << "RR:::::R     R:::::RII::::::IISSSSSSS     S:::::SK:::::::K   K::::::K" << endl;
	cout << "R::::::R     R:::::RI::::::::IS::::::SSSSSS:::::SK:::::::K    K:::::K" << endl;
	cout << "R::::::R     R:::::RI::::::::IS:::::::::::::::SS K:::::::K    K:::::K" << endl;
	cout << "RRRRRRRR     RRRRRRRIIIIIIIIII SSSSSSSSSSSSSSS   KKKKKKKKK    KKKKKKK" << endl;
	cout << endl;
}

vector<Player*> Instantiation::getPlayers() const
{
	return players;
}

void Instantiation::randomizePlayerOrder()
{
	vector<Player*> newOrder;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, players.size()-1);

	while (newOrder.size() != players.size())
	{
		int dice_roll = distribution(generator);  // generates number in the range 0..maxPlayers
		Player* p = players[dice_roll];

		if (p != nullptr)
		{
			newOrder.push_back(p);
			players[dice_roll] = nullptr;
		}
	}
	players = newOrder;
}