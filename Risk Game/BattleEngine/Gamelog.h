#pragma once
#include "BattleEngine.h"
#include "../BattleEngine/Player.h"
#include "../Map/Country.h"
#include<vector>
using namespace std;

//Decorative Game Log Pattern
class GameLog{
	public:
		virtual void Info(Player *a_Player) = 0;//pure virtual fonction

};

class PlayerLog : public GameLog{
		
public:
	void Info(Player *a_Player) {

		cout << "\nPlayer : " << a_Player->getName() << " owns the following countries : " << endl;

		vector<Country*> playerCountries = a_Player->getCountries();
		
		//Displays all the countries owned by the player.
		for (vector<Country*>::iterator it = playerCountries.begin(); it != playerCountries.end(); ++it){
			cout << (*it)->getName() << endl;
		}
	}

};

class PlayerArmiesLog : public PlayerLog{

public:
	void Info(Player *a_Player) {

		cout << "\nPlayer : " << a_Player->getName() << " owns the following countries : " << endl;

		vector<Country*> playerCountries = a_Player->getCountries();

		for (vector<Country*>::iterator it = playerCountries.begin(); it != playerCountries.end(); ++it){
			cout << (*it)->getName() << " Current number of armies : " << (*it)->getNumArmies() << endl;
		}
	}

};

//This class decorate the Info class by adding the total Number of battle won and the card type owned.
class AllPlayerInfo : public PlayerArmiesLog {

public:
	void Info(Player *a_Player){

		 PlayerArmiesLog::Info(a_Player);
		
		 cout << "\nTotal number of Battle won : " << a_Player->getBattlesWonTotal() << endl;
	}
};