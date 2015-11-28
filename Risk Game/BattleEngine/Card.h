#pragma once
using namespace std;
#include <iostream>
#include <string>
#include <random>

class Card
{


public:
	Card();
	~Card();
	string getCardSuit();

private:
	string suit;
	string IMG_FILE_LOCATION; //TODO: we need to select files and how we will implement in GUI
	int num_cards_dealt; //tracks total number of cards dealt, incremented upon each instantiation (Not used anywhere)
};

