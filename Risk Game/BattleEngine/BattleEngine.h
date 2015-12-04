#pragma once 

#include "Player.h"
#include "../Map/Country.h"
#include "../Validation.h"

#include <iostream> 
#include <iomanip>
#include <string>
#include <algorithm>
#include <functional>
#include <random>

using std::cout;
using std::wcout;
using std::cin;
using std::endl;
using std::setw;
using std::sort;
using std::min;
using std::greater;
using std::string;

class Country;
class Player;

class BattleEngine
{

private:

	static int attackerRoll(Player* attackerPlayer, Player* defenderPlayer, Country *attackerCountry, Country *defenderCountry);
	static bool isAttackOver(int attackerNum_armies, int defenderNum_armies);
	static bool defenderLost(Country* attackerCountry, Country *defenderCountry, int attackerNum_armies, int defenderNum_armies);
	static bool attackerLost(Country* attackerCountry, Country *defenderCountry, int attackerNum_armies, int defenderNum_armies);
	static void compareRolls(Country *attackerCountry, Country* defenderCountry, int* attackerRollsList, int* defenderRollsList, int attackerNumRoll, int defenderNumRoll);
	static int* generateDescSortedRollList(int size);
	
	static void displayBattleInfo(Player* attackerPlayer, Player* defenderPlayer, Country* attackerCountry, Country* defenderCountry);
	static void displayDefenderLost();
	static void displayAttackerLost();

public:
	static bool attack(Country *attacker, Country *defender);
	static bool isContinue();
	static bool isAllInMode(Player *attackerPlayer);
	static int numberOfArmiesToSend(Player* attackerPlayer, int numberOfRolls, int attackerNumArmies);
};