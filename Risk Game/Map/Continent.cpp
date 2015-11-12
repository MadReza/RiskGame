//CHRISTOPHER KRAJEWSKI 25189209
//COMP 345 ASSIGNMENT 2

#include "Continent.h"


Continent::Continent(string n, int o)
{
	name = n;
	complete_occupation_value = o;
}

Continent::~Continent()
{
	for (int i = 0; i != countries.size(); i++)		
	{		
		delete countries[i];		
	}
}

void Continent::addCountriesToContinent(Country* c)
{
	countries.push_back(c);//adds countries to the end of the vector
	countries.back()->setContinent(this); //after country is added, the country's containing continent is set
}

vector<Country*> Continent::getContinentVector()
{
	return countries;
}

string Continent::getContinentName()
{
	return name;
}

void Continent::setVisited()
{
	visited = true;
}

bool Continent::getVisited()
{
	return visited;
}

void Continent::setContinentOwner(Player * player)	//TODO: Maybe Renaming ????
{
	continent_owner = player;
	continent_owner->addContinent(this);	//TODO We need For Removing Continents from previous owners.
}

Player * Continent::getContinentOwner()
{
	return continent_owner;
}

void Continent::checkAndSetContinentOwner()
{
	for (int i = 0; i != countries.size(); i++)
	{
		Player* first = countries[0]->getOwner();
		Player* second = countries[i]->getOwner();

		if (first != second)
		{
			//set continent owner to nullptr
			//if they are never equivalent
			this->setContinentOwner(nullptr);
			break;
		}

		//If we get to the end of the vector array without breaking,
		//then all owners are the same
		//so just set the owner to the first vector index
		if (i == (countries.size() - 1))
		{
			this->setContinentOwner(countries[0]->getOwner());
		}

	}
}

int Continent::getOccupationValue()
{
	return complete_occupation_value;
}
