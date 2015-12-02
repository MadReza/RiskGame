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
	//TODO LOAD FROM FILE HERE. OR FROM GAME DRIVER
	cout << "Game is loading...." << endl;
	isNewGame = false;
	totalPlayers = 3;
	mapPath = 1;
	return;
	// map creation
	string str(Directory::GetCurrentWorkingDirectory());
	const char* cd = str.c_str();
	string path = Directory::CombinePaths(2, cd, "Mapfiles");
	vector<string> maps(Directory::GetFilesNamesFrom(path));
	mapPath = path + "\\" + maps[2];
	UtilityMap m(mapPath);
	map = m.getMapObject();

	// players creation
	players.push_back(new Player("p1", Player::Human));
	players.push_back(new Player("p2", Player::Human));
	players.push_back(new Player("p3", Player::Human));

	// countries assignation to players
	//map->distributePlayers(players); this is random distribution
	/*
	TODO: Assign countries to players
	foreach player
		vector<int> continents_indices; // load continent indices
		continents_indices.push_back(1);
		continents_indices.push_back(3);
		continents_indices.push_back(4);

		foreach continent
			vector<int> countries_indices; // load country indices in continent
			countries_indices.push_back(1);
			countries_indices.push_back(3);
			countries_indices.push_back(4);
			foreach country
				map->assignCountryToPlayer(player, continent_index, countries_indices) // assign country to player
	*/
	_game = GameDriver::getInstance();
	_game->setTotalPlayers(3);
	_game->setPlayers(getPlayers());
	_game->setSelectedMap(getMap());

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
		cin >> totalPlayers;
	} while (totalPlayers <= 1 || totalPlayers > map->getMaxPlayers());

	do
	{
		cout << "How many Human Players(0 to " << totalPlayers << "): ";
		cin >> totalHumanPlayers;
	} while (totalHumanPlayers < 0 || totalHumanPlayers > totalPlayers);

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
		cin >> selection;
	} while (selection < 0 || selection >= size);

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
	int selection(-1);
	cout << "Type 0: To Start a New Game" << endl;
	cout << "Type 1: To Load a Game" << endl;
	cout << "Type 2: To Create a Map" << endl;
	cout << "Selection: ";
	cin >> selection;

	while (selection < 0 || selection > 2)
	{
		cout << "Only allowed options are 0, 1, 2: ";
		cin >> selection;
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