/*Utility class for manipulating cards consisting exclusively of static methods*/

#pragma once
#include "Card.h"
#include "Player.h"

class CardUtilities{

public:
	static bool checkRedemption(Player* p);
	static void selectRedemption(Player* p);
	static void displayPlayerCards(Player* p);

private:
	CardUtilities();
	~CardUtilities();

};
