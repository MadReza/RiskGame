#pragma once

#include "Strategy.h"
#include "../Map/Country.h"
#include "../Subject.h"
#include "CardUtilities.h"

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
	bool turnVictory;

	// Attributes related to cards
	vector<Card*> cards;
	int _cardRedemptionsTotal = 0;
	bool redeemThisTurn;	//TODO @chris maybe rename this ?? 
	
	void initialize();
	Country* selectPlayerCountry(bool showArmy = false, int showWithMinArmy = 0);
	Country* Player::selectAdjacentEnemyCountriesTo(Country* country);

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
	void setTurnVictory(bool trueFalse);
	bool getTurnVictory();
	void setRedeemThisTurn(bool trueFalse);
	bool getRedeemThisTurn();
	void resetRoundVariables();

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
	int getCardReinforcementTotal();
    int getBattlesWonTotal();

	void assignReinforcements();
	void assignAttack();

	bool getAlive();
	void setAlive(bool trueFalse);

	vector<Country*> getCountries();	//TODO restrict access to countries.... !!!

	//Card Methods
	vector<Card*> getCards();
	void incrementCardRedemptionsTotal();
	int getCardRedemptionsTotal();
};

