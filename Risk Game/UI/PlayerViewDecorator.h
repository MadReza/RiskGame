#pragma once
#include "../UI/PlayerView.h"
#include "../Map/Country.h"
#include "../Screen.h"

#include <iostream>
#include <string>
#include<vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Player;
class PlayerView;

//Decorative Player view Pattern

class PlayerViewDecorator : public PlayerView{
private:
	bool startedScreenOutput = false;
	COORD gameCursorCoordinates;
public:

	PlayerViewDecorator(Player *p) : PlayerView(*p){
		
		if (!risk::obsDisplaying)
		{
			risk::obsDisplaying = true;
			startedScreenOutput = true;
			gameCursorCoordinates = risk::getCursorPosition();
			risk::clsObserver();
		}
		
		//pass reference to a player object
		Player *a_Player(p);

		cout << "\n" << a_Player->getName() << " Owned Countries : " << endl;
		vector<Country*> playerCountries = a_Player->getCountries();

		//Displays all the countries owned by the player with their armies.
		for (vector<Country*>::iterator it = playerCountries.begin(); it != playerCountries.end(); ++it){
			cout << (*it)->getName() << " - Current number of armies : " << (*it)->getNumArmies() << endl;
		}
		cout << endl;
		PlayerView::update();
	}

	~PlayerViewDecorator(){
		if (startedScreenOutput)
		{
			risk::setCursorPosition(gameCursorCoordinates);
			risk::obsDisplaying = false;
		}
	}

};

//This class decorate the Info class by adding the total Number of battle won and the cards owned.
class CompletePlayerView : public PlayerViewDecorator {
private:
	bool startedScreenOutput = false;
	COORD gameCursorCoordinates;

public:
	//Decorate the already existing Playerview Decorator
	CompletePlayerView(Player *p) : PlayerViewDecorator(p){

		if (!risk::obsDisplaying)
		{
			risk::obsDisplaying = true;
			startedScreenOutput = true;
			gameCursorCoordinates = risk::getCursorPosition();
			risk::clsObserver();
		}

		CardUtilities::displayPlayerCards(p);
	}

	~CompletePlayerView(){
		if (startedScreenOutput)
		{
			risk::setCursorPosition(gameCursorCoordinates);
			risk::obsDisplaying = false;
		}
	}
};