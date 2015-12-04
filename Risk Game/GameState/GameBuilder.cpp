#include "GameBuilder.h"

using namespace std;

GameBuilder::GameBuilder(char* filename) {
	this->_filename = filename;
	this->_game = new Instantiation();
	_game->setIsNewGame(false);
}

void GameBuilder::buildMap() {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(_filename);

	if (result)
	{
		// SAVE FILE LOADED CORRECTLY
		pugi::xml_node save = doc.child("save");
		pugi::xml_node map = save.child("map");

		//	GET THE MAP
		string str(Directory::GetCurrentWorkingDirectory());
		const char* cd = str.c_str();
		string path = Directory::CombinePaths(2, cd, "Mapfiles");
		string mapPath = path + "\\" + map.child_value();
		_game->setMapPath(mapPath);
		_game->setMapFilename(map.child_value());
		UtilityMap m(mapPath);
		_game->setMap(m.getMapObject());
	}
	else
	{
		//	SAVE FILE DID NOT LOAD CORRECTLY
		cout << "Save file did not load correctly: " << result.description() << "\n";
	}
}

void GameBuilder::buildPlayers() {
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(_filename);

	if (result)
	{
		// SAVE FILE LOADED CORRECTLY
		pugi::xml_node save = doc.child("save");
		pugi::xml_node players = save.child("players");

		// GET THE PLAYERS
		for (pugi::xml_node player = players.child("player"); player; player = player.next_sibling("player"))
		{
			//	CREATE THE PLAYER
			Player* p;

			Player::Type type;
			if (strcmp(player.attribute("type").as_string(), "human") == 0)
			{
				type = Player::Human;
				_game->setTotalHumanPlayers(_game->getTotalHumanPlayers() + 1);
			}
			else
			{
				type = Player::Computer;
				_game->setTotalCompPlayers(_game->getTotalCompPlayers() + 1);
			}

			string name = player.attribute("name").value();

			p = new Player(name, type);
			vector<Player*> players_vector = _game->getPlayers();
			players_vector.push_back(p);
			_game->setPlayers(players_vector);

			// INCREMENT THE NUMBER OF PLAYERS
			_game->setTotalPlayers(_game->getTotalPlayers() + 1);

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
				Map* gameMap = _game->getMap();
				gameMap->assignCountriesToPlayer(p, continent_index, countries_indices, armies);
			}
		}
	}
	else
	{
		//	SAVE FILE DID NOT LOAD CORRECTLY
		cout << "Players did not load correctly: " << result.description() << "\n";
	}
}

Instantiation* GameBuilder::getGame() {
    return _game;
}
