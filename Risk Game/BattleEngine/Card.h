#pragma once

#include "CardUtilities.h"

#include <iostream>
#include <string>
#include <random>

using std::string;

class CardUtilities;
enum CardType;

class Card
{

public:
	Card();
	Card(CardType type);
	~Card();
	CardType getCardSuit();
	string getImgFileLocation();

private:
	CardType suit;
	string IMG_FILE_LOCATION; //TODO: we need to select files and how we will implement in GUI
	static int num_cards_dealt; //tracks total number of cards dealt, incremented upon each instantiation
};

