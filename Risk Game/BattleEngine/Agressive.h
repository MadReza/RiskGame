#include "Strategy.h"
#include<vector>
using namespace std;

//Derived class
class Agressive : public Strategy{

public:
	void useStrategy(Country *c1){

		vector<Country*> VectorCountry = c1->getAdjacencyVector();

		for (vector<Country*>::iterator it = VectorCountry.begin(); it != VectorCountry.end(); ++it){
			if (c1->getNumArmies() > (*it)->getNumArmies()){
				BattleEngine(c1, *it);
				break;
			}
		}

		cout << "\t Computer Turns End" << endl;

	}; 
};