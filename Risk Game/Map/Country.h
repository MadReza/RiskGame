#pragma once
using namespace std;
#include<string>
#include "../BattleEngine/Player.h"
#include<vector>
#include "Continent.h"

//This Class can be conceived of as equivalent to a Node class, with extra data members for this RISK implementation. Edges to nodes of objects of this type
//are stored in Adjacent_Countries.

class Continent; //forward declaration
class Player;

class Country
{
private:
	string name; 
	int num_armies{ 0 }; //number of armies currently occupying the country
	int x_coordinate, y_coordinate; //used and set when parsing from a map .txt file
	bool visited{ false };  //used to confirm connected graph in DFS graph traversal, set to true upon being visited
	bool reinforcementVisit{ false };

	
	Player *owner = nullptr; //TODO Update	
	vector<Country*> Adjacent_Countries; //stores all the country edges for this country	
	Continent* containing_continent; //the continent the country is contained in, it is set when the country is added to a continent only

public:
	Country(string n);
	Country(string n, int x, int y); //this constructor will be used for the GUI and the Reading/Writing maps due to specified coordinates
	Country(string nameOfCountry, Player *ownerID, int numberOfarmies); 
	~Country();
	
	void addAdjacentCountry(Country* c); //Used to add adjacent countries or edges to the Adjacent_Countries vector
	void setOwner(Player *p); //sets the Player owner of this country
	Player* getOwner(); //Return owner of the country
	string getName(); //returns object name
	int getNumArmies(); //returns the number of armies currently occupying this country
	bool getVisited(); //used in the .isConnectedGraph() method in the Map class, it returns true if the country was visited during the DFS
	void setVisited(bool b); //sets visited attribute to true
	void setXCoordinate(int x); //for use in the GUI and to store values from the database of pre-existing maps
	void setYCoordinate(int y);
	vector<Country*> getAdjacencyVector(); //Returns the vector of edges for this country
	void displayAdjacentCountries();
	void addArmies(int add); //adds specified integer value of armies to this country
	void setContinent(Continent* continent);
	string getContinentName();
	Continent* getContinentObject(); //return pointer to containing continent
	bool checkIfOwned(); //checks if country is presently occupied

	int getX();
	int getY();
	void setReinforcementVisit(bool s);
	bool getReinforcementVisit();
};

