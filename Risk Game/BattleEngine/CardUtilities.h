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

class CardUtilities{

public:
	static bool checkRedemption(Player* p);
	static void selectRedemption(Player* p);
	static void displayPlayerCards(Player* p);
	/*This method transfers all the cards from Player a to Player b.
	Call this only when player a is defeated by Player b.*/
	static void takePlayerCards(Player* a, Player* b); 
	/* If the player wins a battle, add one card to his hand */
	static void getVictoryCard(Player* p);
	/*The number of reinforcements for a successful card redemption will
	increase with every subsequent redemptions*/
	static int getRedemptionReinforcements(Player* p);
	static void removeThreeSimilar(Player* p, string s);
	static void removeThreeDiff(Player* p);


private:
	CardUtilities();
	~CardUtilities();

};
