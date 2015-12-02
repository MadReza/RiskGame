#pragma once 

#include "Player.h"
#include "../Map/Country.h"

#include <iostream> 
#include <iomanip>
#include <string>
#include <cstdlib>		//Random Generator
#include <ctime>
#include <algorithm>	//sort algorithm used
#include <functional>

using std::cout;
using std::wcout;
using std::cin;
using std::endl;
using std::setw;
using std::sort;
using std::greater;
using std::string;

class Country;
class Player;

class BattleEngine
{
private:
	Player *attackerPlayer;
	Player *defenderPlayer;
	Country *attackerCountry;
	Country *defenderCountry;

	int attackerRoll();
	void displayBattleInfo();
	bool isAttackOver(int attackerNum_armies, int defenderNum_armies);
	bool defenderLost(int attackerNum_armies, int defenderNum_armies);
	bool attackerLost(int attackerNum_armies, int defenderNum_armies);
	void compareRolls(int* attackerRollsList, int* defenderRollsList, int attackerNumRoll, int defenderNumRoll);
	int* generateDescSortedRollList(int size);

	int roll(int min = 1, int max = 6);

	void displayDefenderLost();
	void displayAttackerLost();

public:
	BattleEngine(Country *attacker, Country *defender);
	~BattleEngine();

	void attack(); 
	bool isContinue();
	bool isAllInMode();
	int numberOfArmiesToSend(int numberOfRolls, int attackerNumArmies);
};