#include "MapCreator.h"

#include <iostream>

std::MapCreator::MapCreator()
{
	system("cls");
	cout << "\nWELCOME TO" << endl; 
	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	cout << "===============================================================================" << endl;
	cout << "MM    MM   AAA   PPPPPP   CCCCC  RRRRRR  EEEEEEE   AAA   TTTTTTT  OOOOO  RRRRRR" << endl;
	cout << "MMM  MMM  AAAAA  PP   PP CC    C RR   RR EE       AAAAA    TTT   OO   OO RR   R" << endl;
	cout << "MM MM MM AA   AA PPPPPP  CC      RRRRRR  EEEEE   AA   AA   TTT   OO   OO RRRRRR" << endl;
	cout << "MM    MM AAAAAAA PP      CC    C RR  RR  EE      AAAAAAA   TTT   OO   OO RR  RR" << endl;
	cout << "MM    MM AA   AA PP       CCCCC  RR   RR EEEEEEE AA   AA   TTT    OOOO0  RR   RR" << endl;
	cout << "===============================================================================" << endl;
	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	cout << "\nWhat would you like to do?" << endl;
	cout << "0: exit" << endl;
	cout << "1: edit" << endl;
	cout << "2: create" << endl;
	cout << "Enter > ";

	int option = 0;
	bool isComplete;

	while (!std::validInteger(option, 0, 2)){
		cout << "Sorry what was that? Enter > ";
	}

	switch (option) {
		case 0: 
			break;
		case 1: 
			edit();
			break;
		case 2: 
			create();
			break;
	}
	system("cls");
	if(!isEmpty() && isValidMap()){
		int answer;
		do{
			cout << "1:  Yes , 0: No" << endl;
			cout << "Would you like to save this map, " << name << "? Enter >";
		} while (!std::validInteger(answer, 0, 1));

			switch (answer)
			{
			case 1:
				cout << "Saving map... " << endl; 
				writeMapFile(name + ".map");
				cout << "Success" << endl;
				system("cls");
				break;
			case 0:
				cout << "Exiting..." << endl; system("cls");
				break;
			default:
				break;
			}
	}
	else {
		cout << "Looks like the map is empty or not valid?" << endl;
	}
	cout << "Exiting mapcreator.." << endl;
}

std::MapCreator::~MapCreator()
{
}

//================================================================================MAP CREATIION================================================================================
void std::MapCreator::create()
{
	system("cls");
	cout << "\n>>>>>>>>>>>Map Creation Mode<<<<<<<<<<<" << endl;
	cout << ">>>>>>>>>>>>>>>>>>>>>1/5<<<<<<<<<<<<<<<<<" << endl;
	/*
		create
		name, author
		numcoutnry, num continent
		country
		contient
		check
		fix util connected.
	*/
	cout << "What is the new map name? Enter > ";
	cin >> name;
	cout << "Who is the author? Enter > ";
	cin >> author;

	system("cls");
	cout << "\n>>>>>>>>>>>Map Creation Mode<<<<<<<<<<<" << endl;
	cout << ">>>>>>>>>>>>>>>>>>>>>2/5<<<<<<<<<<<<<<<<<" << endl;
	cout << "\nEnter more then 4 countries and 2 continents..\n" << endl;
	int numCountries;

	cout << "How many countries are you creating? Enter > ";
	while (!std::validInteger(numCountries, 4, 255))
	{
		cout << "Enter between 4 and 255, Please > ";
	}

	int numContinents;
	cout << endl << "How many continent are you creating? Enter > ";
	while (!std::validInteger(numContinents, 2, numCountries))
	{
		cout << "Enter between 2 and less then the number of countries. > ";
	}

	system("cls");
	cout << "\n>>>>>>>>>>>Adding Continents<<<<<<<<<<<" << endl;
	cout << ">>>>>>>>>>>>>>>>>>>>>3/5<<<<<<<<<<<<<<<<<" << endl;
	cout << "RULE: Contienents must have more then 2 bonus points\n" << endl;
	for (int i = 0; i < (int)numContinents; i++) {
		cout << endl;
		cout << "For Continent " << i + 1 << endl;
		addContinent();
	}

	system("cls");
	cout << "\n>>>>>>>>>>>>Adding Countries<<<<<<<<<<<" << endl;
	cout << ">>>>>>>>>>>>>>>>>>>>>4/5<<<<<<<<<<<<<<<<<" << endl;
	cout << "\nHere are the current contients created" << endl;
	for (int i = 0; i < (int)numContinents; i++){
		cout << ContinentList[i].getContinentName() << " \n";
	}
	for (int i = 0; i < numCountries; i++) {
		cout << endl;
		cout << "For Country " << i + 1 << endl;
		addCountry();
	}

	system("cls");
	cout << "\n>>>>>>>>Finalizing Map Creation<<<<<<<<" << endl;
	cout << ">>>>>>>>>>>>>>>>>>>>>5/5<<<<<<<<<<<<<<<<<" << endl;
	validate();
}

//================================================================================AddCountry================================================================================
void std::MapCreator::addCountry() 
{
	string name, continent;
	int x, y, numAdj;
	vector<string> adjacentCountry;
	cout << "What is its name? Enter > ";
	cin >> name;

	do {
		cout << "What is the x cordinate? Enter > ";
	} while (!std::validInteger(x, 0, 9999));

	do {
		cout << "What is the y cordinate? Enter > ";
	} while (!std::validInteger(y, 0, 9999));

	cout << "What is the continent of '" << name << "'? Enter > ";
	cin >> continent;

	do {
		cout << "What is the number of adjacent countries? Enter > ";
	} while (!std::validInteger(numAdj, 0, 9999));

	for (int i = 0; i < numAdj; i++) {
		string temp;
		cout << "What is the name of adjacent country? Enter > ";
		cin >> temp;
		adjacentCountry.push_back(temp);
	}

	CountryList.push_back(UtilityCountry(name, x, y, continent, adjacentCountry));
}

//================================================================================AddContinent================================================================================
void std::MapCreator::addContinent() {
	string name; int bonus;
	cout << "What is its name? Enter > ";
	cin >> name;

	do {
		cout << "What is the bonus? Enter > ";
	} while (!std::validInteger(bonus, 2, 20));

	ContinentList.push_back(UtilityContinent(name, bonus));
}

//================================================================================Validation================================================================================
bool std::MapCreator::validate(){
	int option;
	cout << endl << "Checking...";
	if (isEmpty())
		return false;
	while (!isValidMap()) {
		print();
		cout << endl;
		cout << "There was an error" << endl;
		cout << "You must do one of the following to correct the problem: " << endl;
		cout << "0: give up" << endl;
		cout << "1: create continent" << endl;
		cout << "2: remove continent" << endl;
		cout << "3: edit continent" << endl;
		cout << "4: create country" << endl;
		cout << "5: remove country" << endl;
		cout << "6: edit country" << endl;
		cout << "Enter > ";

		while (!std::validInteger(option, 0, 6)){
			cout << "Sorry wrong answer. Try Again > ";
		}

		switch (option) {
			system("cls");
			case 0:
				return false;
			case 1:
				addContinent();
				break;
			case 2:
				removeContinent();
				break;
			case 3:
				editContinent();
				break;
			case 4:
				addCountry();
				break;
			case 5:
				removeCountry();
				break;
			case 6:
				editCountry();
				break;
			}
	}
	return true;
}

//================================================================================Edit Console================================================================================
void std::MapCreator::edit(){
	system("cls");
	cout << "\n>>>>>>>>>>>Map Edit Mode<<<<<<<<<<<\n" << endl;

	cout << "Where is the map file location located?" << endl;
	string fileLocation;
	cin >> fileLocation;
	bufferMapFile(fileLocation);
	if (!isValidMap()) {
		cout << "MapFile Currupted!" << endl;
		system("pause");
		return;
	}

	bool exit = false;
	do {
		system("cls");
		cout << endl;
		print();
		cout << endl;
		int option;
		cout << "0: exit (work may be lost!)" << endl;
		cout << "1: edit map" << endl;
		cout << "2: edit country" << endl;
		cout << "3: edit continent" << endl;
		cout << "4: add country" << endl;
		cout << "5: add continent" << endl;
		do {
			cout << "What would you like to do? Enter > ";
		} while (!std::validInteger(option, 0, 5));

		switch (option) {
			case 0: return;
			case 1: editMap(); break;
			case 2: editCountry(); break;
			case 3: editContinent(); break;
			case 4: addCountry(); break;
			case 5: addContinent(); break;
		}

		while (!isValidMap()) {
			system("cls");
			cout << "A few things need to be corrected before procceding..." << endl;
			validate();
		}

	} while (!exit);
}

//================================================================================Edit Country================================================================================
void std::MapCreator::editCountry(){
	system("cls");
	for (unsigned int i = 0; i < CountryList.size(); i++) {
		cout << i << ": " << CountryList[i].getCountryName() << endl;
	}
	cout << endl;

	cout << "What would you like to do?" << endl;
	cout << "0: exit " << endl;
	cout << "1: change country name." << endl;
	cout << "2: change x point." << endl;
	cout << "3: change y point." << endl;
	cout << "4: change continent." << endl;
	cout << "5: change adjacent country list." << endl;

	int option;
	do {
		cout << "Enter > ";
	} while (!std::validInteger(option, 0, 5));

	if (option == 0)
		return;

	cout << endl;
	int targetCountry;
	do {
		cout << "Which country would you like to edit? Enter Index > ";
		cin >> targetCountry;
	} while (!std::validInteger(targetCountry, 0, (int)CountryList.size() - 1));


	switch (option) {
		case 1: {
				string old = CountryList[targetCountry].getCountryName();
				cout << "What is the new country name of '" << CountryList[targetCountry].getCountryName() << "' ?" << endl;
				string newName;
				cin >> newName;
				CountryList[targetCountry].setCountryName(newName);
				//update map with new country name
				for (unsigned int i = 0; i < CountryList.size(); i++) {
					for (unsigned int k = 0; k < CountryList[i].getAdjacentCountries().size(); k++) {
						if (old.compare(CountryList[i].getAdjacentCountries()[k]) == 0)
							CountryList[i].getAdjacentCountries()[k] = newName;
					}
				}
			}		
			break;
		case 2:
			cout << "What is the new x point of '" << CountryList[targetCountry].getCountryName() << "'?" << endl;
			int xpoint;
			while (!std::validInteger(xpoint, 0, 9999)){
				cout << "Try again: " << endl;
 			}
			CountryList[targetCountry].setX(xpoint);
			break;
		case 3:
			cout << "What is the new y point of '" << CountryList[targetCountry].getCountryName() << "'?" << endl;
			int ypoint;
			while (!std::validInteger(ypoint, 0, 9999)){
				cout << "Try again: " << endl;
			}
			CountryList[targetCountry].setY(ypoint);
			break;
		case 4: {
				cout << "What is the new continent of '" << CountryList[targetCountry].getCountryName() << "'?" << endl;
				cout << "\nHere are the current contients created" << endl;
				for (unsigned int i = 0; i < ContinentList.size(); i++) {
					cout << ContinentList[i].getContinentName() << " \n";
				}
				string newContinent;
				cin >> newContinent;
				CountryList[targetCountry].setContient(newContinent);
			}
			break;
		case 5: {
				cout <<"Here are the current adjacent countries of '" << CountryList[targetCountry].getCountryName() << "'..." << endl;
				for (unsigned int i = 0; i < CountryList[targetCountry].getAdjacentCountries().size(); i++) {
					cout << i << CountryList[targetCountry].getAdjacentCountries()[i] << endl;
				}
				int option;
				cout << "0: remove adjacency";
				cout << "1: add adjacency";
				while (!std::validInteger(option, 0, 1)){
					cout << "Try again: " << endl;
				}
				switch (option) {
				case 0: {
						cout << "which adjacent country would you like to remove? " << endl;
						string remove; //TODO
						for (unsigned int i = 0; i < CountryList[targetCountry].getAdjacentCountries().size(); i++) {
							if (remove.compare(CountryList[targetCountry].getAdjacentCountries()[i]) == 0)
								CountryList[targetCountry].getAdjacentCountries().erase(CountryList[targetCountry].getAdjacentCountries().begin() + i);
						}
					}
					break;
				case 1: {
						cout << "What is the name of the name adjacent country? Enter > ";
						cin >> name;
						CountryList[targetCountry].getAdjacentCountries().push_back(name);
						cout << "Added succesfully!" << endl;
						system("pause");
					}
					break;
				}
			}
			break;
	}
}

//================================================================================EditContinet================================================================================
void std::MapCreator::editContinent(){
	system("cls");
	for (unsigned int i = 0; i < ContinentList.size(); i++){
		cout << i << ": " << ContinentList[i].getContinentName() << endl;
	}
	cout  << endl;

	cout << "What would you like to do?" << endl;
	cout << "0: exit " << endl;
	cout << "1: change continent name." << endl;
	cout << "2: change bonus amount." << endl;

	int option;
	cout << "Enter > ";
	do {
		cout << "Try again > ";
	} while (!std::validInteger(option, 0, 2));

	if (option == 0)
		return;

	int targetContinent;

	do {
		cout << "Which continent would you like to edit? (index?) Enter > ";
	} while (!std::validInteger(targetContinent, 0, (int)ContinentList.size() - 1));

	switch(option) {
		case 1: {
				string old = ContinentList[targetContinent].getContinentName();
				cout << "What is the new contient name of '" << old << "'?" << endl;
				string newName;
				cin >> newName;
				ContinentList[targetContinent].setContinentName(newName);
				for (unsigned int i = 0; i < CountryList.size(); i++){
					if (old.compare(CountryList[i].getContinent()) == 0)
						CountryList[i].setContient(newName);
				}
			}
			break;
		case 2:
			cout << "What is the new bonus, before '" << ContinentList[targetContinent].getBonus() << "'?" << endl;
			int newBonus;

			while (!std::validInteger(newBonus, 2, 20)){
				cout << "Enter bonus greater then 2 > ";
			}

			ContinentList[targetContinent].setBonus(newBonus);
			break;
	}
}
//================================================================================Edit Map Properties================================================================================
void std::MapCreator::editMap(){
	system("cls");
	cout << "Name: " << name << endl;
	cout << "Author: " << author << endl << endl;

	cout << "What would you like to do? " << endl;
	cout << "0: exit " << endl;
	cout << "1: change map name" << endl;
	cout << "2: change author name" << endl;

	int option;

	do {
		cout << "Enter > ";
	} while (!std::validInteger(option, 0, 2));

	switch (option) {
		case 0:	return;
		case 1: 
			cout << "What is the new map name? " << endl;
			cin >> name;
			break;
		case 2: 
			cout << "What is the new author name? " << endl;
			cin >> author;
			break;
	}
}

//================================================================================Remove Country================================================================================
void std::MapCreator::removeCountry(){
	print();
	string target;
	cout << "Which country would you like to remove? Enter > ";
	cin >> target;
	cout << "Searching and destroying..." << endl;
	for (unsigned int i = 0; i < CountryList.size(); i++) {
		if (target.compare(CountryList[i].getCountryName()) == 0) {
			cout << "Erased" << CountryList[i].getCountryName() << endl;
			CountryList.erase(CountryList.begin() + i);
			continue;
		}
		vector<string> temp = CountryList[i].getAdjacentCountries();
		for (unsigned int k = 0; k < temp.size(); k++) {
			if (target.compare(temp[k]) == 0)
				temp.erase(temp.begin() + k);
		}
	}
	system("pause");
}

//================================================================================Remove Continent================================================================================
void std::MapCreator::removeContinent(){
	print();
	string target;
	cout << "!!!!Attention removing continent will remove all the countries in it!!!!" << endl;
	cout << "Which continent would you like to remove? Enter > ";
	cin >> target;
	cout << "Searching and destroying..." << endl;
	int count = 0;
	for (unsigned int i = 0; i < ContinentList.size(); i++) {
		if (target.compare(ContinentList[i].getContinentName()) == 0) {
			ContinentList.erase(ContinentList.begin() + i);
			break;
		}
	}
	for (unsigned int i = 0; i < CountryList.size(); i++){
		if (target.compare(CountryList[i].getContinent()) == 0) {
			CountryList.erase(CountryList.begin() + i);
		}
	}
	cout << "Erased " << count << " reoccurring." << endl;;
	system("pause");
}

