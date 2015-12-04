#pragma once
#include "Strategy.h"
#include "../Screen.h"
#include <iostream>


using std::vector;
using std::cout;

//Derived class
class Agressive : public Strategy{
private:
	string name = "Agressive";

public:
	string getStrategyName(){ return name; };
	void doStrategy(Country *c1){

		vector<Country*> VectorCountry = c1->getAdjacencyVector();
		Country* targetCountry;

		for (vector<Country*>::iterator it = VectorCountry.begin(); it != VectorCountry.end(); ++it){
			if (c1->getNumArmies() > (*it)->getNumArmies()){
				cout << "Computer " << c1->getOwner()->getName() << " decided to attack: " << endl;
				cout << "Attacking from " << c1->getName() << " to " << (*it)->getName() << endl;
				risk::pause();

				bool countryConquered = BattleEngine::attack(c1, (*it));
				Country* targetCountry = (*it);
				Player* defender = targetCountry->getOwner();
				if (!defender->getAlive())
				{
					CardUtilities::takePlayerCards(defender, c1->getOwner());
				}
				break;
			}
		}




		cout << "\t Computer Turns End" << endl;

	}; 
};