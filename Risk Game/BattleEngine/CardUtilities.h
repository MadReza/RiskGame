/*Utility class for manipulating cards consisting exclusively of static methods
TODO:
	-take player cards on defeat DONE
	-victory card DONE
	-get starting hand (CANCEL: their is no starting hand deal)
	-getRedemption rreinforcement number
	-sort hand?
	*/

#pragma once
#include "Card.h"
#include "Player.h"
#include "../Screen.h"

class Card;

enum CardType { Infantry, Artillery, Cavalry };

class CardUtilities{

public:
	static const char* cardTypes[];

	static const int MAX_REDEMPTION_HAND_SIZE = 5;
	
	static bool checkRedemption(Player* p);
	static bool mandatoryRedemption(Player* p);
	static int selectRedemption(Player* p);
	static void displayPlayerCards(Player* p);
	/*This method transfers all the cards from Player a to Player b.
	Call this only when player a is defeated by Player b.*/
	static void takePlayerCards(Player* loser, Player* winner); 
	/* If the player wins a battle, add one card to his hand */
	static void getVictoryCard(Player* p);

	static void print(CardType card);
private:
	CardUtilities();
	~CardUtilities();
	static void deleteSuit(Player *p, CardType suit);
	static void removeThreeSimilar(Player* p, CardType s);
	static void removeThreeDiff(Player* p);
	/*The number of reinforcements for a successful card redemption will
	increase with every subsequent redemptions & return total reinforcement*/
	static int getRedemptionReinforcements(Player* p);
	static void getTotalOfEachCard(Player *p, int &infantry, int &artillery, int &cavalry);	//TODO @chris maybe rename this ??

	static void printInfantry();
	static void printArtillery();
	static void printCavalry();
	static void printBlank();
};
