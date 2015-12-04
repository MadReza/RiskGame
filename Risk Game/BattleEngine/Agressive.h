#pragma once
#include "Strategy.h"
#include <iostream>

using std::vector;
using std::cout;

//Derived class
class Agressive : public Strategy{

public:

	void doStrategy(Country *c1){

		vector<Country*> VectorCountry = c1->getAdjacencyVector();
		Country* targetCountry;

		for (vector<Country*>::iterator it = VectorCountry.begin(); it != VectorCountry.end(); ++it){
			if (c1->getNumArmies() > (*it)->getNumArmies()){
				bool countryConquered = BattleEngine::attack(c1, (*it));
				Country* targetCountry = (*it);
				Player* defender = targetCountry->getOwner();
				if (!defender->getAlive())
				{
					//TODO @Chris test your randomness
					/*defender->getCards()->push_back(new Card());
					system("pause");
					defender->getCards()->push_back(new Card());
					system("pause");
					defender->getCards()->push_back(new Card());
					system("pause");
					defender->getCards()->push_back(new Card());
					system("pause");
					defender->getCards()->push_back(new Card());
					system("pause");
					defender->getCards()->push_back(new Card());*/
					CardUtilities::takePlayerCards(defender, c1->getOwner());
				}
				break;
			}
		}


		cout << "\t Computer Turns End" << endl;

	}; 
};