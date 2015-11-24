#include "Card.h"

Card::Card()
{
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, 2);
	int random_int = distribution(generator);

	if (random_int == 0)
	{
		suit = "INFANTRY";
		IMG_FILE_LOCATION = "infantry.jpg";	//TODO
	}

	if (random_int == 1)
	{
		suit = "ARTILLERY";
		IMG_FILE_LOCATION = "artillery.jpg";	//TODO
	}

	if (random_int == 2)
	{
		suit = "CAVALRY";
		IMG_FILE_LOCATION = "cavalry.jpg";	//TODO
	}

	num_cards_dealt++;
}


Card::~Card()
{
}

string Card::getCardSuit()
{
	return suit;
}






