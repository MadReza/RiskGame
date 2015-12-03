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

	for (int i = 0; i != cards.size(); i++)
	{
		delete cards[i];
	}
}

void Player::initialize()
{
    _armiesTotal = 0;
    _battlesWonTotal = 0;
    _reinforcementTotal = 0;
	resetRoundVariables();
}

void Player::resetRoundVariables()
{
	turnVictory = false;
	redeemThisTurn = false;
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
	cout << "Total Reinforcement from Countries with lower limit of 3: " << max(reinforcement, MIN_REINFORCEMENT) << endl;

	reinforcement = max(reinforcement, MIN_REINFORCEMENT);
	reinforcement += getCardReinforcementTotal();

	return reinforcement;
}

int Player::getCardReinforcementTotal()
{
	char answer;
	int cardReinforcement = 0;
	do {
		system("cls");

		CardUtilities::displayPlayerCards(this);
		cout << "You have redeemed " << getCardRedemptionsTotal() << " times." << endl;
		if (CardUtilities::mandatoryRedemption(this))
		{
			cout << "You have more than or equal to the maximum " << CardUtilities::MAX_REDEMPTION_HAND_SIZE << " cards allowed." << endl;
			cout << "You must redeem below " << CardUtilities::MAX_REDEMPTION_HAND_SIZE << " cards." << endl;
		}

		if (!CardUtilities::checkRedemption(this))	//Nothing to Redeem
		{
			cout << "Nothing to redeem" << endl;
			system("pause");
			system("cls");
			return 0;
		}

		cout << "Do you want to redeem a set of cards (y,n): ";
		cin >> answer;	//TODO validate this
		while (!std::validYes_No(answer)){
			cout << "Try again > ";
		}

		if (answer == 'y' || answer == 'Y')
		{
			cardReinforcement += CardUtilities::selectRedemption(this);
		}

	} while (CardUtilities::mandatoryRedemption(this) && answer != 'n' && answer != 'N' && answer != 'y' && answer != 'Y');

	return cardReinforcement;
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
			/*cin >> selection;*/	//COMPLETED Todo: currently assuming boundry is met. // Done: Zack
		} while (!std::validInteger(selection, 0, countries.size() - 1)/*selection < 0 || selection > (countries.size() -1)*/);

		cout << endl;
		cout << "Select the country to reinforce (" << armyToAssign << " reinforcement left): " << endl;
		Country* countrySelection{ selectPlayerCountry() };

		cout << endl;
		int armyToAdd{ 0 };		
		do {
			cout << countrySelection->getName() << " selected. Enter number of armies to add to country from 0 to " << armyToAssign << ": ";
			cin >> armyToAdd;
		} while (armyToAdd < 0 || armyToAdd > armyToAssign);

		countrySelection->addArmies(armyToAdd);
		armyToAssign -= armyToAdd;
	}
	system("cls"); //COMPLETED TODO: Done by Zack
}

Country* Player::selectAdjacentEnemyCountriesTo(Country* country)
{
	vector<Country*> allAdjacentCountries = country->getAdjacencyVector();
	vector<Country*> enemyAdjacentCountries;

	//Get Enemy Adjacent countries
	for (int x = 0; x < allAdjacentCountries.size(); x++)
	{
		if (allAdjacentCountries[x]->getOwner() != this)
		{
			enemyAdjacentCountries.push_back(allAdjacentCountries[x]);
		}
	}

	//Display Enemy Adjacent Countries to attack
	for (int x = 0; x < enemyAdjacentCountries.size(); x++)
	{
		cout << x << ": " << enemyAdjacentCountries[x]->getName() << ", Army Size: " << enemyAdjacentCountries[x]->getNumArmies() << endl;
	}
	int selection{ -1 };

	do {
		cout << "Select the country number from 0 to " << enemyAdjacentCountries.size() - 1 << ": ";
		cin >> selection;
	} while (selection < 0 || selection >(enemyAdjacentCountries.size() - 1));

	return enemyAdjacentCountries[selection];
}

Country* Player::selectPlayerCountry(bool showArmy, int showWithMinArmy)
{
	vector<Country*> eligibleCountries;

	for (int i = 0; i < countries.size(); i++)
	{
		if (countries[i]->getNumArmies() >= showWithMinArmy)
		{
			eligibleCountries.push_back(countries[i]);
		}
	}

	for (int i = 0; i < eligibleCountries.size(); i++)
	{
		cout << i << ": " << eligibleCountries[i]->getName();
		if (showArmy)
			cout << " Army Size: " << eligibleCountries[i]->getNumArmies();
		cout << endl;
	}
	int selection{ -1 };

	do {
		cout << "Select the country number from 0 to " << eligibleCountries.size() - 1 << ": ";
		cin >> selection;
	} while (selection < 0 || selection >(eligibleCountries.size() - 1));

	return eligibleCountries[selection];
}

int Player::getBattlesWonTotal() {
    return _battlesWonTotal;
}

bool Player::getAlive()
{
	return alive;
}

void Player::setAlive(bool trueFalse)
{
	alive = trueFalse;
}

void Player::addCountry(Country* country)
{
	countries.push_back(country);
}

void Player::removeCountry(Country* country)	//TODO TEST
{
	countries.erase(std::remove(countries.begin(), countries.end(), country), countries.end());
	if (countries.size() == 0)
	{
		setAlive(false);
	}
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

vector<Card*> Player::getCards()
{
	return cards;
}

void Player::incrementCardRedemptionsTotal()
{
	_cardRedemptionsTotal++;
}

int Player::getCardRedemptionsTotal()
{
	return _cardRedemptionsTotal;
}

void Player::assignAttack()
{
	cout << "Select Country to attack from: " << endl;
	Country* attackingCountry(selectPlayerCountry(true,2));					
	cout << endl;
	cout << "Select Country to attack to: " << endl;
	Country* targetCountry(selectAdjacentEnemyCountriesTo(attackingCountry));

	Player* defender = targetCountry->getOwner();
	bool countryConquered = BattleEngine::attack(attackingCountry, targetCountry);

	if (countryConquered && !defender->getAlive())	
	{
		CardUtilities::takePlayerCards(defender, this);
	}
}

void Player::setTurnVictory(bool trueFalse)
{
	turnVictory = trueFalse;
}

bool Player::getTurnVictory()
{
	return turnVictory;
}

void Player::setRedeemThisTurn(bool trueFalse)
{
	redeemThisTurn = trueFalse;
}
bool Player::getRedeemThisTurn()
{
	return redeemThisTurn;
}