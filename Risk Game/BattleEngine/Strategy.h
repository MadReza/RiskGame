#pragma once
#include "BattleEngine.h"
#include "Player.h"
#include "../Map/Country.h"
#include "map"
#include <vector>

class Country;

using namespace std;

//Base class
class Strategy {

public :
	virtual void doStrategy(Country *c1) = 0;// pure virtual fonction
};