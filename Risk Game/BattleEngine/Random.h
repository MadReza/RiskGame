#pragma once
#include "Strategy.h"
#include "../Screen.h"

#include <ctime>
#include <iostream>

using std::vector;
using std::cout;

//Derived class
class Random : public Strategy{
private:
	string name = "Random";

public:
	string getStrategyName(){ return name; };
	void doStrategy(Country *c1){

		vector<Country*> VectorCountry = c1->getAdjacencyVector();
		
		for (vector<Country*>::iterator it = VectorCountry.begin(); it != VectorCountry.end(); ++it){
			if (c1->getNumArmies() > (*it)->getNumArmies()){
				if ((rand() % 2) + 1 == 2){	//To attack or not to attack
					cout << "Computer " << c1->getOwner()->getName() << " decided to attack: " << endl;
					cout << "Attacking from " << c1->getName() << " to " << (*it)->getName() << endl;
					risk::pause();
					bool countryConquered = BattleEngine::attack(c1, (*it));
					Player* defender = (*it)->getOwner();
					if (!defender->getAlive())
					{
						CardUtilities::takePlayerCards(defender, c1->getOwner());
					}
					break;
				}//Random number between 1 and 2. if 2 it will attack
			}
		}

		cout << "\t Computer Turns End" << endl;
	};

};