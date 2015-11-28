#include "Strategy.h"
#include<vector>
using namespace std;

//Derived class
class Agressive : public Strategy{

public:
	//An Agressive player checks if One adjacent enemy country have less countries than it has, Then attack tgat country.
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