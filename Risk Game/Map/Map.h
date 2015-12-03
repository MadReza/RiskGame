//CHRISTOPHER KRAJEWSKI 25189209
//COMP 345 ASSIGNMENT 2

/*The Map class is also the Subject class*/


#pragma once
#include "Continent.h"
#include "Country.h"
#include "../Subject.h"
#include <vector>
#include <random>
#include <algorithm>


using namespace std;

class Map : public Subject
{
public:
	Map(string name,int continents,int countries); //Alternative Constructor
	~Map();
	void addContinentsToMap(Continent* c); //Adds Continents to the Map_Vector
	int getNumContinents();	//returns the number of continents
	int getNumCountries(); //returns num_countries attribute
	bool isConnectedGraphCountries(); //confirms that the DFS of .visitAllCountries was successful
	bool isConnectedGraphContinents();
	bool checkForValidCountryNumber(); //returns false if there are more than 256 countries
	int countCountries();
	//METHOD TO RETURN ALL COUNTRY IN THE MAP AS OBJECTS
	vector<Continent*> getMapVector() const; //returns the Map_Vector
	void visitAllCountries(Country* c); //This method is used to visit all connected countries on the map and set their visited attribute to true.
										//It is a DFS of the country nodes and their edges
	string getMapName(); //Returns map name
	void setContinentOwnership();
	bool checkAllCountriesOwned();

	void distributePlayers(vector<Player*> player_vector); //randomly distributes a vector of players across all countries
	void assignCountriesToPlayer(Player* player, int continent_index, vector<int> countries_indices, vector<int> armies); // assign a player to specific countries of a continent (Not random)
	string getAuthor();
	int getMaxPlayers();

	bool connectedDFS(Player* owner, Country* start, Country* target);
	void resetFortificationDFS();
private:
	const int MIN_COUNTRIES = 10;
	const int MAX_COUNTRIES = 256;
	const int MAX_PLAYERS = 6;
	const int MIN_PLAYERS = 2;

	vector<Continent*> continents; //This resizable container holds all the continent objects
	string name;
	int num_continents; 
	int num_countries;
	string author; //Map Creator's name	

};

