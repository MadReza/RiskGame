#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "UtilityMap.h"
#include "../Validation.h"
//#include "../Directory.h"
//Directory::GetWorkingDirectory()

/*
	Menu Sequence
	-create
		-create map
			-name
			-author
		-map properties
			-num contients
			-num countries
		-create continents
			-name
			-bonus
		-create countries
			-name
			-x
			-y
			-number of adjacent countries
			-for each, name of adjacent
		-validate until map is correct
			-loops the editor
	-edit
		-edit map
		-add continent
		-add


*/
namespace std {
	class MapCreator: public UtilityMap{
		public:
			/*mapcreator program loader, simply calling this is like opening a new window*/
			MapCreator();
			~MapCreator();
			
		private:
			/*map creator*/
			void create();
			/*user country creator*/
			void addCountry();
			/*user contient creator*/
			void addContinent();
			/*user map validator*/
			bool validate();

			/*user editor*/
			void edit();
			/*user country editor*/
			void editCountry();
			/*user contient editor*/
			void editContinent();
			/*map property editor*/
			void editMap();
			/*country remover*/
			void removeCountry();
			/*contient remover*/
			void removeContinent();
			
			void printCountryList();
			void printContientList();
	};

}