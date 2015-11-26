
#pragma once //BattleEngine_H safe include guard
#include <iostream>
#include "../Map/Country.h"
#include "../BattleEngine/Player.h"
#include <string>
using namespace std;

class Country;

class BattleEngine
{
	private:	
	Country *attackerCountry;
	Country *defenderCountry;
	int attackerNum_armies;
	int defenderNum_armies; //Not safe since these variables is available to all the functions (Purpose for Assignment 1)
	int attackerNum_Roll, defenderNum_Roll;
	

public:
	BattleEngine(Country *attackerCountry, Country *defenderCountry);
	~BattleEngine();
	void attack(); //Method declaration
	void generateRollList(int* emptyArray, int size); //Method declaration
	void displayBattleInfo(int attackerNumOfArmies, int defenderNumOfArmies);//Method declaration
	int roll(); //Method declaration
	bool isAttackOver(int attackerNum_armies, int defenderNum_armies); //Method declaration
	bool isContinue(); //Method declaration
	bool isAllInMode();//Method declaration
	int numberOfArmiesToSend(int numberOfRolls, int attackerNumArmies); //Method declaration
};