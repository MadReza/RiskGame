#pragma once
#include "BattleEngine.h"
#include "../Map/Country.h"
#include <vector>
#include <string>

class Country;

//Base class
class Strategy {

public :
	virtual void doStrategy(Country *c1) = 0;// pure virtual fonction
	virtual string getStrategyName() = 0;
};