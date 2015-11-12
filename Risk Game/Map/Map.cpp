//CHRISTOPHER KRAJEWSKI 25189209
//COMP 345 ASSIGNMENT 2

#include "Map.h"
#include<iostream>

Map::Map(string n, int continents, int countries)
{
	name = n;
	num_continents = continents;
	num_countries = countries;
}


Map::~Map()
{
}

void Map::addContinentsToMap(Continent* c)
{
	continents.push_back(c); //adds continents to Map vector
}

int Map::getNumContinents()
{
	num_continents = continents.size();
	return num_continents; 
}


bool Map::isConnectedGraphCountries()
{
	
	for (int i = 0; i != continents.size(); i++)
	{
		int size = continents[i]->getContinentVector().size();

		for (int j = 0; j != continents[i]->getContinentVector().size(); j++)
		{
			
			if (continents[i]->getContinentVector()[j]->getVisited() == false)
			{
				cout << "ERROR: Unvisited country found: " << continents[i]->getContinentVector()[j]->getName() << ". All countries are NOT connected!" << endl;
				return false;
				break;
			}
		}

	}
	cout << "No Unvisited Countries, all the countries are connected!" << endl;
 	return true;
}

bool Map::isConnectedGraphContinents()
{
	for (int i = 0; i != continents.size(); i++)
	{
		if (continents[i]->getVisited() == false)
		{
			cout << "ERROR: Unvisited continent found: " << continents[i]->getContinentName() << ". All Continents are NOT connected!" << endl;
			return false;
			break;
		}
	}

cout << "No Unvisited Continents found, all Continents are connected!" << endl;
return true;
}

bool Map::checkForValidCountryNumber()
{
	if (this->countCountries() > MAX_COUNTRIES || this->countCountries() < MIN_COUNTRIES)
	{
		return false;
	}
	else
		return true;
}

int Map::countCountries()
{
	int counter = 0;
	for (int i = 0; i != continents.size(); i++)
	{
		for (int j = 0; j != continents[i]->getContinentVector().size(); j++)
		{
			counter++;
		}
	}

	num_countries = counter;
	return num_countries;
}

int Map::getNumCountries()
{
	return num_countries;
}


vector<Continent*> Map::getMapVector() const
{
	return continents;
}


void Map::visitAllCountries(Country* c)
{
	if (c->getVisited() == false)
	{
		cout << "Visiting Country: " << c->getName() << endl;
	}

	c->setVisited(true);

	//To visit Continents simultaneously

	if (c->getContinentObject()->getVisited() == false)
	{
		cout << "Visiting Continent: " << c->getContinentName() << endl;
		c->getContinentObject()->setVisited();
	}

	for (int i = 0; i != c->getAdjacencyVector().size(); i++)
	{
		if (c->getAdjacencyVector()[i]->getVisited() != true)
		{
			visitAllCountries(c->getAdjacencyVector()[i]);
		}
	}

}

string Map::getMapName()
{
	return name;
}

void Map::setContinentOwnership()
{
	for (int i = 0; i != continents.size(); i++)
	{
		continents[i]->checkAndSetContinentOwner();
	}
}

bool Map::checkAllCountriesOwned()
{
	for (int i = 0; i != continents.size(); i++)
	{
		for (int j = 0; j != continents[i]->getContinentVector().size(); j++)
		{
			if (continents[i]->getContinentVector()[j]->checkIfOwned() == false)
			{
				//if an unowned country is found, return false
				return false;
			}

		}
	}
	//returns true if there are no unowned countries left
	return true;
}

void Map::distributePlayers(vector<Player*> player_vector)
{
	default_random_engine generator;
	int k = 0;

	//while array of countries is not filled
	while (this->checkAllCountriesOwned() == false)
	{
		uniform_int_distribution<int> continent_distribution(0, (continents.size() - 1));
		int i = continent_distribution(generator);
		
		uniform_int_distribution<int> country_distribution(0, (continents[i]->getContinentVector().size() - 1));
		int j = country_distribution(generator);
		
		Player* next_player = player_vector[k % player_vector.size()];
		
		if (continents[i]->getContinentVector()[j]->checkIfOwned() == false)
		{
			continents[i]->getContinentVector()[j]->setOwner(next_player);
			cout << "Assigned Country: " << continents[i]->getContinentVector()[j]->getName()
				<< ", to Player: " << next_player->getName() << "." << endl;
			k++; //go to next index only if the country was assigned.
		}

	}

}

string Map::getAuthor()
{
	return author;
}

int Map::getMaxPlayers()
{
	if ((this->countCountries() / 7) > MAX_PLAYERS)
	{
		return 6;
	}
	return max(this->countCountries() / 7, MIN_PLAYERS);
}

