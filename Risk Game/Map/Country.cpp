//CHRISTOPHER KRAJEWSKI 25189209
//COMP 345 ASSIGNMENT 2

#include "Country.h"
#include "Continent.h"
#include <iostream>

Country::Country(string n)
{
	name = n;
}

Country::Country(string n, int x, int y)
{
	x_coordinate = x;
	y_coordinate = y;
	name = n;
}

Country::Country(string nameOfCountry, Player *ownerID, int numberOfarmies)
{
	num_armies = numberOfarmies;
	owner = ownerID;
	name = nameOfCountry;
}

Country::~Country()
{
}

void Country::addAdjacentCountry(Country* c)
{
	Adjacent_Countries.push_back(c); 
}


void Country::setOwner(Player *p)
{
	owner = p;	//TODO switching owner, notify of change.... e.g.: army 
	owner->AddCountry(this);
}

Player* Country::getOwner()
{
	return owner;
}

string Country::getName()
{
	return name;
}

int Country::getNumArmies()
{
	return num_armies;
}

bool Country::getVisited()
{
	return visited;
}

void Country::setVisited(bool b)
{
	visited = b;
}

void Country::setXCoordinate(int x)
{
	x_coordinate = x;
}
void Country::setYCoordinate(int y)
{
	x_coordinate = y;
}

vector<Country*> Country::getAdjacencyVector()
{
	return Adjacent_Countries;
}

void Country::displayAdjacentCountries()
{

	for (int i = 0; i != Adjacent_Countries.size(); i++)
	{
		cout << Adjacent_Countries[i]->getName() << ", ";
	}

}

void Country::addArmies(int add)
{
	num_armies = num_armies + add;
	owner->CalculateTotalArmies();	//TODO find difference and add only that.
}

void Country::setContinent(Continent * continent)
{
	containing_continent = continent;
}

string Country::getContinentName()
{
	return this->containing_continent->getContinentName();
}

Continent * Country::getContinentObject()
{
	return containing_continent;
}

bool Country::checkIfOwned()
{
	if (this->getOwner() == nullptr)
	{
		return false;
	}

	else
		return true;
}

int Country::getX()
{
	return x_coordinate;
}

int Country::getY()
{
	return y_coordinate;
}



