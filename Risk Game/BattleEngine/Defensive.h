#pragma once
#include "Strategy.h"
#include "../Map/Country.h"

#include <ctime>
#include <iostream>

using std::vector;
using std::cout;


class Defensive : public Strategy {

public:

	void doStrategy(Country *c1){

		srand((unsigned)time(0));
		vector<Country*> vectorcountry = c1->getAdjacencyVector();
		bool isgonna_attack = true;

		for (vector<Country*>::iterator it = vectorcountry.begin(); it != vectorcountry.end(); ++it){
			if (c1->getNumArmies() < (*it)->getNumArmies())
				isgonna_attack = false; 
		}

		if (isgonna_attack){
			int r = rand() % vectorcountry.size();
			BattleEngine::attack(c1, vectorcountry[r]);
		}

		cout << "\t computer turns end" << endl;
	};

};