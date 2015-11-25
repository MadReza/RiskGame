#include "Strategy.h"
#include <ctime>
using namespace std;

//Derived class
class Random : public Strategy{

public:
	//Will randomly decide whether to attack a valid adjacent enemy country.
	void doStrategy(Country *c1){

		srand((unsigned)time(0));
		vector<Country*> VectorCountry = c1->getAdjacencyVector();
		
		for (vector<Country*>::iterator it = VectorCountry.begin(); it != VectorCountry.end(); ++it){
			if (c1->getNumArmies() > (*it)->getNumArmies()){
				if ((rand() % 2) + 1 == 2){
					BattleEngine(c1, *it);
					break;
				}//Random number between 1 and 2. if 2 it will attack
			}
		}

		cout << "\t Computer Turns End" << endl;
	};
};