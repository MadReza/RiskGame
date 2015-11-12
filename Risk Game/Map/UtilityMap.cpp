#include "UtilityMap.h"

//Exception InvalidMapObjectException
class InvalidMapObjectException : public exception
{
	virtual const char* what() const throw()
	{
		return "InvalidMapObjectException";
	}
} InvalidMapObjectException;

/*******************************
Empty Map
*******************************/
std::UtilityMap::UtilityMap()
{
}

/*******************************
Import from MapObject
*******************************/
std::UtilityMap::UtilityMap(Map &MapObject) {
	bufferMapObject(MapObject);
}

/*******************************
Import from fileMapLocation
*******************************/
std::UtilityMap::UtilityMap(string fileLocation)
{
	bufferMapFile(fileLocation);
}

void std::UtilityMap::print()
{
	cout << "Printing Map" << endl;
	cout << endl << "[Continents]" << endl;
	for (unsigned int i = 0; i < ContinentList.size(); i++){
		cout << ContinentList[i].getContinentName() << "=" << ContinentList[i].getBonus() << endl;
	}
	cout << endl;

	cout << endl << "[Territories]" << endl;					//GET NUM CONTUNRY***, WHERE IS
	for (unsigned int i = 0; i < CountryList.size(); i++) {
		cout << CountryList[i].getCountryName()
			<< "," << CountryList[i].getX()
			<< "," << CountryList[i].getY()
			<< "," << CountryList[i].getContinent();
		for (unsigned int j = 0; j < CountryList[i].getAdjacentCountries().size(); j++) {
			cout << "," << CountryList[i].getAdjacentCountries()[j];
		}
		cout << endl;
	}
}

/*******************************
Buffer from MapObject
*******************************/
void std::UtilityMap::bufferMapObject(Map &MapObject) {
	name = MapObject.getMapName();
	author = MapObject.getAuthor();
	vector<Continent*> RealContinentList = MapObject.getMapVector();

	ContinentList.empty();
	CountryList.empty();
	for (unsigned int i = 0; i < RealContinentList.size(); i++) {
		ContinentList.push_back(UtilityContinent(RealContinentList[i]->getContinentName(), RealContinentList[i]->getOccupationValue()));
		vector<Country*> RealCountryList = RealContinentList[i]->getContinentVector();
		for (unsigned int j = 0; j < RealCountryList.size(); j++) {
			vector<string> adjCountries;
			for (unsigned int k = 0; k < RealCountryList[i]->getAdjacencyVector().size(); k++) {
				adjCountries.push_back(RealCountryList[i]->getAdjacencyVector()[k]->getName());
			}
			CountryList.push_back(UtilityCountry(RealCountryList[i]->getName(), RealCountryList[i]->getX(), RealCountryList[i]->getY(), RealContinentList[i]->getContinentName(), adjCountries));
		}
	}
}

/*******************************
Buffer from fileMapLocation
*******************************/
void std::UtilityMap::bufferMapFile(string fileLocation) {

	name = (fileLocation.substr(0, fileLocation.find('.')));

	fstream mapFile;
	mapFile.open(fileLocation, ios::in);

	//temporary storage of values
	string line; //the current line
	string value; //a value of a property
	string name; //the property
	string section; //section track

	while (!mapFile.eof()) {

		getline(mapFile, line, '\n');

		if (line.empty()) continue;

		if (line[0] == '[') { //UPDATES SECTION DEPENDING ON WHERE IT IS
			section = line.substr(1, line.length() - 2);
			continue;
		}

		/*MAP FILE SETTINGS EXTRACTION*/
		if (section.compare("Map") == 0) { //EXTRACTS MAP INFO
			int equalSign = line.find('=');
			name = line.substr(0, equalSign);
			value = line.substr(equalSign + 1, line.length() - 1);

			if (name.compare("author") == 0) {	//we only have author to extract, if need more, add more if conditions for image, wrap..
				author = value;
			}

			continue;
		}
		/*END OF MAP FILE SETTING*/

		/*CONTINENT SECTION EXTRACTION*/
		if (section.compare("Continents") == 0) { //EXTRACTS CONTINENTS
			int equalSign = line.find('=');
			name = line.substr(0, equalSign);
			value = line.substr(equalSign + 1, line.length() - 1);

			UtilityContinent temp(name, std::stoi(value));
			ContinentList.push_back(temp);
			continue;
		}
		/*END OF CONTINENT SECTION EXTRACTION*/

		/*TERRITORY SECTION EXTRACTION*/
		if (section.compare("Territories") == 0) {
			UtilityCountry temp;
			vector<string> adjacentCountries;

			bool end = false; //extracting each word in the line seperated by a comma.
			int TYPE = 0;

			/*WHILE LOOP EXTRACTS THE VALUES IN EACH COUNTRY LINE*/
			while (!end) {
				/*GET VALUE OF EACH ELEMENT IN THE LINE*/
				int commas = line.find(',');
				if (commas == -1) {
					commas = line.length();
					end = true;
				}
				value = line.substr(0, commas);
				if (!end) line = line.substr(commas + 1, line.length());
				/*END OF GET VALUE*/

				/*INSERTION OF VALUES TO TEMPORARY COUNTRY DEPENDING ON POSITION OF TYPE*/
				switch (TYPE) {
				case 0:	//NAME
					temp.setCountryName(value);
					break;
				case 1: //X CORDINATE
					temp.setX(stoi(value, 0, 10));
					break;
				case 2:	//Y CORDINATE
					temp.setY(stoi(value, 0, 10));
					break;
				case 3:	//CONTINENT
					temp.setContient(value);
					break;
				default: //ADJACENT COUNTRIES
					adjacentCountries.push_back(value);
				}
				/*END OF INSERTION*/
				TYPE++;
			} /*END OF WHILE LOOP*/

			temp.setAdjacentCountries(adjacentCountries);
			CountryList.push_back(temp);
			continue;
		}
		/*END OF TERRITORY SECTION EXTRACTION*/

	} /*END OF FILE EXTRACTION*/

}

/*******************************
Constructs the Map object from the UtilityMap Class.
*******************************/
Map* std::UtilityMap::getMapObject(){
	if (isEmpty())
		throw InvalidMapObjectException;

	Map* theMapObject = new Map(name, ContinentList.size(), CountryList.size());

	vector<Continent* > RealContinentObjects;
	map<string, int> CountryHashTable;
	map<string, int> ContinentHashTable;
	std::map<string, int>::iterator it;
	
	/*******************************
		Creation of Continents.
	*******************************/
	for (unsigned int i = 0; i < ContinentList.size(); i++){
		RealContinentObjects.push_back(new Continent(ContinentList[i].getContinentName(), ContinentList[i].getBonus()));
		ContinentHashTable[ContinentList[i].getContinentName()] = i;
		theMapObject->addContinentsToMap(RealContinentObjects[i]);
		//cout << ContinentList[i].getContinentName() << " Created Successfully!" << endl;
	}
	
	/*******************************
		Creation of Country.
	*******************************/
	vector<Country*> RealCountryObjects; 
	
	for (unsigned int i = 0; i < CountryList.size(); i++){
		RealCountryObjects.push_back(new Country(CountryList[i].getCountryName(), CountryList[i].getX(), CountryList[i].getY()));
		CountryHashTable[CountryList[i].getCountryName()] = i;
		//add country to continent
		it = ContinentHashTable.find(CountryList[i].getContinent());
		if (ContinentHashTable.end() == it) {
			cout << "Could not find this continent ->" << CountryList[i].getContinent() << "." << endl;
			throw InvalidMapObjectException;
		}
		int index = ContinentHashTable[CountryList[i].getContinent()];
		RealContinentObjects[index]->addCountriesToContinent(RealCountryObjects[i]);
		//cout << CountryList[i].getCountryName() << " added to " << RealContinentObjects[index]->getContinentName() << endl;
				
	}
	/*******************************
		Adjacency of Countries.
	*******************************/
	for (unsigned int i = 0; i < CountryList.size(); i++){//for each country
		for (unsigned int j = 0; j < CountryList[i].getAdjacentCountries().size(); j++){//for each adjacentcountry find country object and link.
			it = CountryHashTable.find(CountryList[i].getAdjacentCountries()[j]);
			if (CountryHashTable.end() == it) {
				cout << "Could not find this country ->" << CountryList[i].getAdjacentCountries()[j] << "." << endl;
				throw InvalidMapObjectException;
			}
			int index = CountryHashTable[CountryList[i].getAdjacentCountries()[j]];
			RealCountryObjects[i]->addAdjacentCountry(RealCountryObjects[index]);
			//cout << RealCountryObjects[index]->getName() << " Added to " << RealCountryObjects[i]->getName() << endl;
		}
	}

	theMapObject->visitAllCountries(RealCountryObjects[0]);
	if (!theMapObject->isConnectedGraphCountries() || !theMapObject->isConnectedGraphContinents()) 
		throw InvalidMapObjectException;
	return theMapObject;
}

/*******************************
Writes to from UtilityMap to File
*******************************/
bool std::UtilityMap::writeMapFile(string fileLocation) {
	if (isEmpty())
		throw InvalidMapObjectException;
	fstream mapFile;
	mapFile.open(fileLocation, ios::out);

	//MAP SETTINGS
	mapFile << "[Map]" << endl;
	string settings[5] = { "author=","image=","wrap=","scroll=","warn=" };
	for (int i = 0; i < 5; i++) {
		mapFile << settings[i];
		switch (i) {
		case 0:
			mapFile << author << endl; break;
		default:
			mapFile << "" << endl;
		}
	}

	//FOR EACH CONTINENT..			
	mapFile << endl << "[Continents]" << endl;
	for (unsigned int i = 0; i < ContinentList.size(); i++)
	{
		mapFile << ContinentList[i].getContinentName() << "=" << ContinentList[i].getBonus() << endl;
	}

	//EACH COUNTRY
	mapFile << endl << "[Territories]" << endl;					//GET NUM CONTUNRY***, WHERE IS
	for (unsigned int i = 0; i < CountryList.size(); i++) {
		mapFile << CountryList[i].getCountryName()
			<< "," << CountryList[i].getX()
			<< "," << CountryList[i].getY()
			<< "," << CountryList[i].getContinent();
		for (unsigned int j = 0; j < CountryList[i].getAdjacentCountries().size(); j++) {
			mapFile << "," << CountryList[i].getAdjacentCountries()[j];
		}
		mapFile << endl;
	}
	return true;
}

bool std::UtilityMap::isValidMap() {
	try{
		getMapObject();
	} catch (const std::exception&) {
		return false;
	}
	return true;
}

std::UtilityContinent::UtilityContinent() : UtilityContinent("EMPTY", 0)
{
}

std::UtilityContinent::UtilityContinent(string Name, int BonusArmies) : name(Name), bonus(BonusArmies)
{
}


std::UtilityCountry::UtilityCountry()
{
	name = "EMPTY";
	x = 0; y = 0; 
	continent = "EMPTY";
	vector<string> adjacentCountries;
}

std::UtilityCountry::UtilityCountry(string Name, int X, int Y, string Continent, vector<string> AdjacentCountries):name(Name), x(X), y(Y), continent(Continent), adjacentCountries(AdjacentCountries)
{
}
