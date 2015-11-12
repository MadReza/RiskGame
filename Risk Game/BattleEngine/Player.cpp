#include "Player.h"

Player::Player()
{
	initialize();
}

Player::Player(string name, Type type_Player)
{
	_name = name;
	typeOfPlayer = type_Player;
	initialize();
}

Player::Player(string name, Strategy *strat)
{
	_name = name;
	typeOfPlayer = Computer;
	Astrategy = strat;
	initialize();
}

Player::~Player()
{
	delete Astrategy;
}

void Player::initialize()
{
    _armiesTotal = 0;
    _battlesWonTotal = 0;
    _reinforcementTotal = 0;
}

Player::Type Player::getType()
{
	return typeOfPlayer;
}

void Player::setName(string name)
{
	_name = name;
}

string Player::getName()
{
	return _name;
}

void Player::setPlayerStrategy(Strategy *strat)
{
	Astrategy = strat;
}

bool Player::isHuman(Player p)
{
	if (p.getType() == Player::Human)
		return true;
	else
		return false;
}

//TODO: @Kendy or @Zack: We are currently looping a lot ... maybe get a better way ? As we add 1 to every country...
void Player::calculateTotalArmies()
{
	_armiesTotal = 0;
	for each (Country* country in countries)
	{
		_armiesTotal += country->getNumArmies();
	}
	notify();
}


void Player::setBattlesWonTotal(int n) {
    _battlesWonTotal = n;
    notify();
}

int Player::getArmiesTotal() {
    return _armiesTotal;
}

int Player::getReinforcementTotal() {
	int reinforcement{0};
	reinforcement += countries.size() / 3;
	cout << "Bonus From Countries: " << reinforcement << endl;;
	for each (Continent* continent in continents)
	{
		reinforcement += continent->getOccupationValue();
		cout << "Bonus From Continent: " << continent->getContinentName() << " is " << continent->getOccupationValue() << endl;	
	}
	cout << "Total Reinforcement with lower limit of 3: " << max(reinforcement, MIN_REINFORCEMENT) << endl;
	return max(reinforcement, MIN_REINFORCEMENT);
}

void Player::assignReinforcements()
{
	int armyToAssign{getReinforcementTotal()};

	while (armyToAssign > 0)
	{
		for (unsigned int i = 0; i < countries.size(); i++)
		{
			cout << i << ": " << countries[i]->getName() << endl;
		}
		int selection{-1};
		
		do {
			cout << "Select the country number from 0 to " << countries.size()-1 << ": ";			//COMPLETED TODO CLEAN THIS FUNCTION e.g.:Boundry // Done: Zack
			cin >> selection;	//COMPLETED Todo: currently assuming boundry is met. // Done: Zack
		} while (selection < 0 || selection > (countries.size()-1));

		int armyToAdd{ 0 };
		
		do {
			cout << countries[selection]->getName() << " selected. Enter number of armies to add to country from 0 to " << armyToAssign << ": ";
			cin >> armyToAdd;
		} while (armyToAdd < 0 || armyToAdd > armyToAssign);

		countries[selection]->addArmies(armyToAdd);
		armyToAssign -= armyToAdd;
	}
	system("cls"); //COMPLETED TODO: Done by Zack
}

int Player::getBattlesWonTotal() {
    return _battlesWonTotal;
}

bool Player::getAlive()
{
	return alive;
}

void Player::addCountry(Country* country)
{
	countries.push_back(country);
}

void Player::removeCountry(Country* country)	//TODO TEST
{
	countries.erase(std::remove(countries.begin(), countries.end(), country), countries.end());
}

void Player::addContinent(Continent* continent)	//TODO TEST
{
	continents.push_back(continent);
}
void Player::removeContinent(Continent* continent)
{
	continents.erase(std::remove(continents.begin(), continents.end(), continent), continents.end());
}

vector<Country*> Player::getCountries()
{
	return countries;
}