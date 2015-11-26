#pragma once
#include "Player.h"
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

	//info of the PlayerLog class
	void Info(Player *a_Player) {

		cout << "\n\n" << a_Player->getName() << " owns the following countries : " << endl;

		vector<Country*> playerCountries = a_Player->getCountries();
		
		//Displays all the countries owned by the player.
		for (vector<Country*>::iterator it = playerCountries.begin(); it != playerCountries.end(); ++it){
			cout << (*it)->getName() << endl;
		}
		cout << endl;
	}

};

class PlayerArmiesLog : public PlayerLog{

public:
	
	//info of the PlayerArmiesLog class
	void Info(Player *a_Player) {

		cout << "\n\n" << a_Player->getName() << " owns the following countries : " << endl;

		vector<Country*> playerCountries = a_Player->getCountries();

		for (vector<Country*>::iterator it = playerCountries.begin(); it != playerCountries.end(); ++it){
			cout << (*it)->getName() << " - Current number of armies : " << (*it)->getNumArmies() << endl;
		}
		cout << endl;
	}

};

//This class decorate the Info class by adding the total Number of battle won and the card type owned.
class CompletePlayerLog : public PlayerArmiesLog {

public:
		//info of the CompletePlayerLog class
		void Info(Player *a_Player){
			PlayerArmiesLog::Info(a_Player);

		 cout << "\nTotal number of Battle won : " << a_Player->getBattlesWonTotal() << endl;
		 //cout << "Cards owned " << a_Player->getCards() << endl; Will display the cards
	}
};