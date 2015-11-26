#include "BattleEngine/Player.h"
#include "Country.h"
#include <vector>

class Gamelog {
public : 
	virtual void Info(Player *a_Player) = 0;

};


class Playerlog : public Gamelog {
public:

	void Info(Player *a_Player){
 		vector<Country*> playerCountries = a_Player->getCountries();

		for (vector<Country*>::iterator it = playerCountries.begin(); it != playerCountries.end(); ++it){
			cout << (*it)->getName();
		}
	}
};