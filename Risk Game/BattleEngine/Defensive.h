#pragma once
#include "Strategy.h"
#include <ctime>

class Defensive : public Strategy {

public:
	//A defensive player checks if all adjacent enemy country have less countries than it has, Then attack a random adjacent enemy country.
	void doStrategy(Country *c1){

		srand((unsigned)time(0));
		vector<Country*> VectorCountry = c1->getAdjacencyVector();
		bool isGonna_Attack = true;
		
		for (vector<Country*>::iterator it = VectorCountry.begin(); it != VectorCountry.end(); ++it){
			if (c1->getNumArmies() < (*it)->getNumArmies())
				isGonna_Attack = false; 
		}

		if (isGonna_Attack){
			int r = rand() % VectorCountry.size();
			BattleEngine(c1, VectorCountry[r]);
		}

		cout << "\t Computer Turns End" << endl;
	};

};