//CHRISTOPHER KRAJEWSKI 25189209
//COMP 345 ASSIGNMENT 2

#pragma once
#include "Country.h"
#include "../BattleEngine/Player.h"

#include <vector>

class Country; //forward declaration
class Player;

using namespace std;

class Continent
{
public:
	Continent(string n, int o);
	~Continent();
	void addCountriesToContinent(Country* c); //adds country pointers to country objects to the Continent Vector
	vector<Country*> getContinentVector(); //returns a Continent_Vector
	string getContinentName(); //returns the name of the continent
	void setVisited(); //sets the continent bool visited to true. Used for traversal alg accounting
	bool getVisited();	//returns the value of bool visited. Used for traversal alg accounting
	void setContinentOwner(Player* player);
	Player *getContinentOwner();
	void checkAndSetContinentOwner();
	int getOccupationValue();

private:
	vector<Country*> countries;//this container holds the country objects 
	string name; //Continent name
	int complete_occupation_value; // number of bonus armies for occupying all the countries on this continent, set upon creation
	bool visited = false;
	Player* continent_owner = nullptr;
};

