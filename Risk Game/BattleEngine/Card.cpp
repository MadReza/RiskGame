#include "Card.h"

int Card::num_cards_dealt = 0;

Card::Card()
{
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, 2);
	int random_int = distribution(generator);

	switch (random_int)
	{
	case 0:
		suit = Infantry;
		IMG_FILE_LOCATION = "infantry.jpg";	//TODO
		break;
	case 1:
		suit = Artillery;
		IMG_FILE_LOCATION = "artillery.jpg";	//TODO
		break;
	case 2:
		suit = Cavalry;
		IMG_FILE_LOCATION = "cavalry.jpg";	//TODO
		break;
	default:
		break;
	}
	num_cards_dealt++;	//Maybe do Card::num_cards_dealt++; 
}


Card::~Card()
{
}

CardType Card::getCardSuit()
{
	return suit;
}
