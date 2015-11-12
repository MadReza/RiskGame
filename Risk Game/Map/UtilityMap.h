#pragma once

#include "Map.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <exception>

using namespace std;

namespace std{

	class UtilityCountry;
	class UtilityContinent;

	/****************************************************************
	AUTHOR: Laurendy Lam. Version 11.11.2015

	SO WHAT IS THE MAP UTILITY CLASS?
		It is a buffer between a map file, and the actual map object. It holds data of a Map Object
	that is going to be later on created with the getMapObject function. It's used to load the 
	map, save a map, or create a map. Map Objects leaving this class need to be valid connected graphs.

	HOW TO USE.
	STEP 1: Use proper constructor, load the map object, or mapfileLocation.
	STEP 2: Use getMapObject or write to map file.

	
	****************************************************************/
	class UtilityMap
	{
	public:
		UtilityMap();
		UtilityMap(Map &Object);
		UtilityMap(string fileLocation);

		string getMapName() { return name; }
		void setMapName(string NewMapName) { name = NewMapName; }

		string getAuthor() { return author; }
		void setAuthor(string NewAuthor) { author = NewAuthor; }

		vector<UtilityContinent> getContients() { return ContinentList; }
		void setContients(vector<UtilityContinent> NewSetContients) { ContinentList = NewSetContients; };

		vector<UtilityCountry> getCountries() { return CountryList; }
		void setCountries(vector<UtilityCountry> NewSetCountries) { CountryList = NewSetCountries; }

		void print();
		Map* getMapObject();
		bool writeMapFile(string fileLocation);

		bool isEmpty() { return CountryList.size() == 0; }

		void bufferMapFile(string fileLocation);
		void bufferMapObject(Map &MapObject);
	private:
		string name;
		string author;

		vector<UtilityContinent> ContinentList;
		vector<UtilityCountry> CountryList;
	};


	class UtilityContinent
	{
	public:
		UtilityContinent();
		UtilityContinent(string Name, int BonusArmies);

		string getContinentName() { return name; }
		void setContinentName(string NewContinentName) { name = NewContinentName; }

		int getBonus() { return bonus; }
		void setBonus(int NewBonus) { bonus = NewBonus; }

	private:
		string name;
		int bonus;
	};

	class UtilityCountry
	{
	public:
		UtilityCountry();
		UtilityCountry(string Name, int X, int Y, string Continent, vector<string> AdjacentCountries);

		string getCountryName() { return name; }
		void setCountryName(string NewCountryname) { name = NewCountryname; }

		int getX() { return x; }
		void setX(int NewX) { x = NewX; }

		int getY() { return y; }
		void setY(int NewY) { y = NewY; }

		string getContinent() { return continent; }
		void setContient(string NewContinent) { continent = NewContinent; }

		vector<string> getAdjacentCountries() { return adjacentCountries; }
		void setAdjacentCountries(vector<string> NewAdjacentCountries) { adjacentCountries = NewAdjacentCountries; }

	private:
		string name;
		int x;
		int y;
		string continent;
		vector<string> adjacentCountries;
	};
}