#pragma once
#include "Strategy.h"
#include "../Map/Country.h"
#include "../Screen.h"

#include <ctime>
#include <iostream>


using std::vector;
using std::cout;


class Defensive : public Strategy {
private:
	string name = "Defensive";

public:
	string getStrategyName(){ return name; };
	void doStrategy(Country *c1){

		vector<Country*> vectorcountry = c1->getAdjacencyVector();
		bool isgonna_attack = true;

		for (vector<Country*>::iterator it = vectorcountry.begin(); it != vectorcountry.end(); ++it){
			if (c1->getNumArmies() < (*it)->getNumArmies())
				isgonna_attack = false; 
		}

		if (isgonna_attack){
			int r = rand() % vectorcountry.size();
			cout << "Computer " << c1->getOwner()->getName() << " decided to attack: " << endl;
			cout << "Attacking from " << c1->getName() << " to " << vectorcountry[r]->getName() << endl;
			risk::pause();

			bool countryConquered = BattleEngine::attack(c1, vectorcountry[r]);
			Player* defender = vectorcountry[r]->getOwner();
			if (!defender->getAlive())
			{
				CardUtilities::takePlayerCards(defender, c1->getOwner());
			}
		}

		cout << "\t computer turns end" << endl;
	};


};