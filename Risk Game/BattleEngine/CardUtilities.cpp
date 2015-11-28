#include "CardUtilities.h"

bool CardUtilities::checkRedemption(Player * p)
{
	int infantry_count = 0, artillery_count = 0, cavalry_count = 0;

	if (p->getCards().size() == 5)
	{
		return true;
	}

	for (int i = 0; i != p->getCards().size(); i++)
	{
		if (p->getCards()[i]->getCardSuit() == "INFANTRY")
		{
			infantry_count++;
		}
		if (p->getCards()[i]->getCardSuit() == "ARTILLERY")
		{
			artillery_count++;
		}
		if (p->getCards()[i]->getCardSuit() == "CAVALRY")
		{
			cavalry_count++;
		}
	}

	//if there is 3 of a kind of any suit return true
	if (infantry_count >= 3 || artillery_count >= 3 || cavalry_count >= 3)
	{
		return true;
	}

	//if there is at least one of each suit return true
	if (infantry_count >= 1 && artillery_count >= 1 && cavalry_count >= 1)
	{
		return true;
	}
	
	return false;
	
}

void CardUtilities::selectRedemption(Player * p)
{
	//TODO: This implementation will be dependent on how we implement the GUI
}

void CardUtilities::displayPlayerCards(Player * p)
{
	//TODO: Dependent on how we implement a GUI
}



CardUtilities::~CardUtilities()
{

}
