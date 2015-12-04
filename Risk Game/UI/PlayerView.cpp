#include "PlayerView.h"

PlayerView::~PlayerView()
{
	_player->detach(this);
}

PlayerView::PlayerView(Player &p) {
    p.attach(this);
    _player = &p;
    _armiesTotal = 0;
    _battlesWonTotal = 0;
    _reinforcementTotal = 0;
}

void PlayerView::update(){
	if (!risk::obsDisplaying)
	{
		risk::obsDisplaying = true;
		startedScreenOutput = true;
		gameCursorCoordinates = risk::getCursorPosition();
		risk::clsObserver();
	}

    _reinforcementTotal = 0;	//TODO @CHRIS @REZA reinforcement call in player was  ouputting shit.
	_continentReinforcements = _player->getContinentReinforcements();
	_countryReinforcements = _player->getCountryReinforcements();
    _armiesTotal = _player->getArmiesTotal();
    _battlesWonTotal = _player->getBattlesWonTotal();

    //Lets print on console just to test the working
    std::cout << "The view was updated for "<< _player->getName() <<" :"<< std::endl;
    std::cout << " - Total Number of armies is now "<< _armiesTotal << std::endl;
	std::cout << " - Total Number of Continent reinforcement is now " << _continentReinforcements << std::endl;
	std::cout << " - Total Number of Country reinforcement is now " << _countryReinforcements << std::endl;
	std::cout << " - Total Number of reinforcement is now " << _reinforcementTotal << std::endl;
    std::cout << " - Total Number of battles won is now "<< _battlesWonTotal << std::endl << std::endl;

	if (startedScreenOutput)
	{
		risk::setCursorPosition(gameCursorCoordinates);
		risk::obsDisplaying = false;
	}
}
