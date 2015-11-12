#include "Player.h"

Player::Player()
{
	Initialize();
}

Player::Player(string name, Type type_Player)
{
	_name = name;
	typeOfPlayer = type_Player;
	Initialize();
}

Player::Player(string name, Type type_Player, Strategy *strat)
{
	_name = name;
	typeOfPlayer = type_Player;
	Astrategy = strat;
	Initialize();
}

Player::~Player()
{
}

void Player::Initialize()
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

void Player::CalculateTotalArmies()		//TODO: @Kendy or @Zack: We are currently looping a lot ... maybe get a better way ? As we add 1 to every country...
{
	_armiesTotal = 0;
	for each (Country* country in countries)
	{
		_armiesTotal += country->getNumArmies();
	}
    Notify();
}

void Player::SetBattlesWonTotal(int n) {
    _battlesWonTotal = n;
    Notify();
}

int Player::GetArmiesTotal() {
    return _armiesTotal;
}

int Player::GetReinforcementTotal() {
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

void Player::AssignReinforcements()
{
	int armyToAssign{GetReinforcementTotal()};

	while (armyToAssign > 0)
	{
		for (int i = 0; i < countries.size(); i++)
		{
			cout << i << ": " << countries[i]->getName() << endl;
		}
		int selection{-1};
		cout << "Select the country number from 0 to " << countries.size()-1 << ": ";			//TODO CLEAN THIS FUNCTION e.g.:Boundry
		cin >> selection;	//Todo: currently assuming boundry is met.
		
		int armyToAdd{ 0 };
		cout << countries[selection]->getName() << " selected. Enter number of armies to add to country from 0 to " << armyToAssign << ": ";
		cin >> armyToAdd;

		countries[selection]->addArmies(armyToAdd);
		armyToAssign -= armyToAdd;
	}
}

int Player::GetBattlesWonTotal() {
    return _battlesWonTotal;
}

bool Player::GetAlive()
{
	return alive;
}

void Player::AddCountry(Country* country)
{
	countries.push_back(country);
}

void Player::RemoveCountry(Country* country)	//TODO TEST
{
	countries.erase(std::remove(countries.begin(), countries.end(), country), countries.end());
}

void Player::AddContinent(Continent* continent)	//TODO TEST
{
	continents.push_back(continent);
}
void Player::RemoveContinent(Continent* continent)
{
	continents.erase(std::remove(continents.begin(), continents.end(), continent), continents.end());
}