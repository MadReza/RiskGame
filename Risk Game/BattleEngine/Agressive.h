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

		for (vector<Country*>::iterator it = VectorCountry.begin(); it != VectorCountry.end(); ++it){
			if (c1->getNumArmies() > (*it)->getNumArmies()){
				BattleEngine::attack(c1, *it);
				break;
			}
		}

		cout << "\t Computer Turns End" << endl;

	}; 
};