#pragma once

#include "Strategy.h"
#include "../Map/Country.h"
#include "../Subject.h"

#include <vector>
#include <string>
#include <set>
#include <algorithm>

using std::string;
using std::set;

class Country;
class Continent;

class Player : public Subject 
{
public :
	enum Type { Human, Computer };
	enum Color
	{
		Red,
		Green,
		White,
		Yellow
	};

private:
	const int MIN_REINFORCEMENT = 3;

	bool alive{true};
	Color color;
	string _name;
	int _reinforcementTotal;
    int _armiesTotal;
    int _battlesWonTotal;
	Type typeOfPlayer;
	Strategy *Astrategy;
	Country *c1;
	//TODO change vector to set for duplicates. @kendy & @Zack
	vector<Country*> countries;	//TODO: DO we need adjacent ???? or just my own ? See @Zack
	vector<Continent*> continents;
	
	void Initialize();

public:
	Player();
	Player(string name, Type typeOfPlayer);
	Player(string name, Type typeOfPlayer, Strategy *strat);	//TODO if strategy is not set for Player. Remove third parameter and force initilization till set.
	~Player();
	Type getType();
	void setName(string name);
	string getName();
	void setPlayerStrategy(Strategy *strat);
	bool isHuman(Player p);
	
	void doStrategy(){
		Astrategy->doStrategy(c1);
	}
	
	void AddCountry(Country* country);
	void RemoveCountry(Country* country);
	void AddContinent(Continent* continent);
	void RemoveContinent(Continent* continent);
	void CalculateTotalArmies();
    void SetBattlesWonTotal(int n);
    int GetArmiesTotal();
    int GetReinforcementTotal();
    int GetBattlesWonTotal();

	void AssignReinforcements();

	bool GetAlive();
};

