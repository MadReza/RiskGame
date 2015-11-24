#pragma once

#include "Strategy.h"
#include "../Map/Country.h"
#include "../Subject.h"




#include <vector>
#include <string>
#include <algorithm>


using std::string;

//forward declarations
class Card;
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
	vector<Country*> countries;	
	vector<Continent*> continents;

	// Attributes related to cards
	vector<Card*> cards;
	int _cardRedemptionsTotal;
	
	void initialize();

public:
	Player();
	Player(string name, Type typeOfPlayer);
	Player(string name, Strategy *strat);	
	~Player();
	Type getType();
	void setName(string name);
	string getName();
	void setPlayerStrategy(Strategy *strat);
	bool isHuman(Player p);
	
	void doStrategy(Country* country){
		Astrategy->doStrategy(country);
	}
	
	void addCountry(Country* country);
	void removeCountry(Country* country);
	void addContinent(Continent* continent);
	void removeContinent(Continent* continent);
	void calculateTotalArmies();
    void setBattlesWonTotal(int n);
    int getArmiesTotal();
    int getReinforcementTotal();
    int getBattlesWonTotal();

	void assignReinforcements();

	bool getAlive();
	vector<Country*> getCountries();	//TODO restrict access to countries.... !!!

	//Card Methods
	vector<Card*> getCards();
	void incrementCardRedemptionsTotal();
	int getCardRedemptionsTotal();
};

