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
	//delete Astrategy;

	for (int i = 0; i != cards->size(); i++)
	{
		delete (*cards)[i];
	}
}

void Player::initialize()
{
    _armiesTotal = 0;
    _battlesWonTotal = 0;
    _reinforcementTotal = 0;
	cards = new vector<Card*>();
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


Strategy* Player::getPlayerStrategy()
{
	return Astrategy;
}


bool Player::isHuman()
{
	if (getType() == Player::Human)
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
	//notify(); //TODO Commetted out for debugging game play
}


void Player::setBattlesWonTotal(int n) {
    _battlesWonTotal = n;
    //notify(); //TODO Commetted out for debugging game play
}

int Player::getArmiesTotal() {
    return _armiesTotal;
}

bool Player::ownsContinent(Continent* continent)
{
	for each (Country* country in continent->getContinentVector())
	{
		if (find(this->countries.begin(), this->countries.end(), country) == this->countries.end()) // if the continent country is not found in the player's countries
			return false;
	}
	return true;
}


int Player::getCountryReinforcements()
{
	return countries.size() / 3;
}

int Player::getContinentReinforcements()
{
	int reinforcement{ 0 };
	set<Continent*> continents_touched_by_player;
	for each (Country* country in this->countries)
	{
		continents_touched_by_player.insert(country->getContinentObject()); // set of continents where the player owns a country
	}
	for each (Continent* continent in continents_touched_by_player)
	{
		if (this->ownsContinent(continent)) 
		{
			reinforcement += continent->getOccupationValue();
			cout << "Bonus From Continent: " << continent->getContinentName() << " is " << continent->getOccupationValue() << endl;
		}
	}
	return reinforcement;
}

int Player::getReinforcementTotal() {
	int reinforcement{0};
	reinforcement += getCountryReinforcements();
	cout << "Bonus From Countries: " << reinforcement << endl;
	
	reinforcement += getContinentReinforcements();
	cout << "Total Reinforcement from Countries with lower limit of 3: " << max(reinforcement, MIN_REINFORCEMENT) << endl;

	reinforcement = max(reinforcement, MIN_REINFORCEMENT);
	reinforcement += getCardReinforcementTotal();

	cout << endl;
	cout << "Total Reinforcment: " << reinforcement << endl;
	risk::pause();

	return reinforcement;
}

int Player::getCardReinforcementTotal()	//TODO: @chris & @kendy, auto cards if computer
{
	char answer;
	int cardReinforcement = 0;
	do {

		CardUtilities::getVictoryCard(this);
		CardUtilities::getVictoryCard(this);
		CardUtilities::getVictoryCard(this);
		CardUtilities::getVictoryCard(this);
		CardUtilities::getVictoryCard(this);

		CardUtilities::displayPlayerCards(this);	//TODO should be an used or called by an observer or something
		cout << "You have redeemed " << getCardRedemptionsTotal() << " times." << endl;
		if (CardUtilities::mandatoryRedemption(this))
		{
			cout << "You have more than or equal to the maximum " << CardUtilities::MAX_REDEMPTION_HAND_SIZE << " cards allowed." << endl;
			cout << "You must redeem to a hand size of less than " << CardUtilities::MAX_REDEMPTION_HAND_SIZE << " cards." << endl;
		}

		if (!CardUtilities::checkRedemption(this))	//Nothing to Redeem
		{
			cout << "Nothing to redeem" << endl;
			system("pause");
			system("cls");
			return 0;
		}

		cout << "Do you want to redeem a set of cards (y,n): ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			cardReinforcement += CardUtilities::selectRedemption(this);
		}

	} while (CardUtilities::mandatoryRedemption(this) || !std::validYesNo(answer));

	cout << "Reinforcements from card redemption: " << cardReinforcement;

	return cardReinforcement;
}

void Player::assignReinforcements()
{	
	int armyToAssign{getReinforcementTotal()};

	while (armyToAssign > 0)
	{
		risk::clsGame();
		cout << "Assigning Reinforcements" << endl;
		cout << "===================" << endl;

		cout << endl << "Select the country to reinforce (" << armyToAssign << " reinforcement left): " << endl;
		Country* countrySelection{ selectPlayerCountry() };

		cout << endl;	
		int armyToAdd = 0;

		do {
			if (!isHuman())
			{
				cout << "\nComputer : " << this->getName() << " selected " << countrySelection->getName();
				armyToAdd = armyToAssign;
				cout << "\nComputer : " << this->getName() << " Added " << armyToAdd << " Armies to " << countrySelection->getName() << endl;
				risk::pause();
				break;
			}
			cout << countrySelection->getName() << " selected. Enter number of armies to add to country from 0 to " << armyToAssign << ": ";
		} while (!std::validInteger(armyToAdd, 0, armyToAssign));

		countrySelection->addArmies(armyToAdd);
		armyToAssign -= armyToAdd;
	}
}

Country* Player::selectAdjacentEnemyCountriesTo(Country* country)
{
	vector<Country*> allAdjacentCountries = country->getAdjacencyVector();
	vector<Country*> enemyAdjacentCountries;

	//Get Enemy Adjacent countries
	for (int x = 0; x < (int)allAdjacentCountries.size(); x++)
	{
		if (allAdjacentCountries[x]->getOwner() != this)
		{
			enemyAdjacentCountries.push_back(allAdjacentCountries[x]);
		}
	}

	if ((int)enemyAdjacentCountries.size() == 0) return NULL;

	//Display Enemy Adjacent Countries to attack
	for (int x = 0; x < (int)enemyAdjacentCountries.size(); x++)
	{
		cout << x << ": " << enemyAdjacentCountries[x]->getName() << ", Army Size: " << enemyAdjacentCountries[x]->getNumArmies() << endl;
	}
	int selection{ -1 };

	do {
		cout << "Select the country number from 0 to " << enemyAdjacentCountries.size() - 1 << ": ";
	} while (!std::validInteger(selection, 0, enemyAdjacentCountries.size() - 1));

	return enemyAdjacentCountries[selection];
}

Country* Player::selectPlayerCountry(bool showArmy, int showWithMinArmy)
{
	vector<Country*> eligibleCountries;

	for (int i = 0; i < (int)countries.size(); i++)
	{
		if (countries[i]->getNumArmies() >= showWithMinArmy)
		{
			eligibleCountries.push_back(countries[i]);
		}
	}

	if (eligibleCountries.size() == 0) return NULL;

	for (int i = 0; i < (int)eligibleCountries.size(); i++)
	{
		cout << i << ": " << eligibleCountries[i]->getName();
		if (showArmy)
			cout << " Army Size: " << eligibleCountries[i]->getNumArmies();
		cout << endl;
	}
	int selection;

	do {
		if (isHuman())
		{
			cout << "Select the country number from 0 to " << eligibleCountries.size() - 1 << ": ";
		}
		else //If this Player is a computer
		{
			srand(time(0));
			selection = eligibleCountries.size() > 1 ? rand() % (eligibleCountries.size() - 1) : 0; //Computer choose from 0 to eligible # of country
			break;
		}
	} while (!std::validInteger(selection, 0, eligibleCountries.size() - 1));

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

vector<Card*>* Player::getCards()
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

bool Player::assignAttack()	//TODO maybe return false if there is no country to be able to attack from or attack to ?  .... Maybe better to do this in GameDriver and make sure its possible.
{
	cout << "Select Country to attack from: " << endl;
	Country* attackingCountry(selectPlayerCountry(true, 2));
	cout << endl;

	vector<Country*> eligibleCountries;

	for (int i = 0; i < (int)countries.size(); i++)
	{
		eligibleCountries.push_back(countries[i]);
	}


	if (eligibleCountries.size() == 0){
		cout << "Looks like there are no eligible coutries to attack with..." << endl;
		return false;
	}

	if (isHuman())
	{
		cout << "Select Country to attack from: " << endl;
		cout << endl;
	}
	else
	{		
		vector<Country*> eligibleCountries;

		for (int i = 0; i < (int)countries.size(); i++)
		{
			if (countries[i]->getNumArmies() >= 2)
			{
				eligibleCountries.push_back(countries[i]);
			}
		}
		this->doStrategy(attackingCountry);
		return true;
	}

	cout << endl;
	cout << "Select Country to attack: " << endl;
	Country* targetCountry(selectAdjacentEnemyCountriesTo(attackingCountry)); //returning elegible attacking adjacent country

	if (targetCountry == NULL){ 
		cout << "Looks like there are no enemies near to attack..." << endl;
		return false;
	}

	Player* defender = targetCountry->getOwner();
	
	if(isHuman())
		bool countryConquered = BattleEngine::attack(attackingCountry, targetCountry);

	if (!defender->getAlive())	
	{		
		CardUtilities::takePlayerCards(defender, this);
	}
	return true;
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