#include "Card.h"

int Card::num_cards_dealt = 0;

Card::Card()
{
	int random_int = rand() % 3;

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

Card::Card(CardType type)
{
	this->suit = type;
}


Card::~Card()
{
}

CardType Card::getCardSuit()
{
	return suit;
}

string Card::getImgFileLocation()
{
	string filename;

	switch (this->suit)
	{
		case Infantry:
			filename = "infantry.jpg";	//TODO
			break;
		case Artillery:
			filename = "artillery.jpg";	//TODO
			break;
		case Cavalry:
			filename = "cavalry.jpg";	//TODO
			break;
	}

	return filename;
}

