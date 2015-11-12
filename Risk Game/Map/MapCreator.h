#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "UtilityMap.h"
//#include "../Directory.h"
//Directory::GetWorkingDirectory()


namespace std {
	class MapCreator: public UtilityMap{
		public:
			MapCreator();
			~MapCreator();
			
		private:
			void create();
			void addCountry();
			void addContinent();
			bool validate();

			void edit();
			void editCountry();
			void editContinent();
			void editMap();
			void removeCountry();
			void removeContinent();
			
	};

}