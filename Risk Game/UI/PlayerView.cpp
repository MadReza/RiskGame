#include "PlayerView.h"

PlayerView::PlayerView(Player &p) {
    p.attach(this);
    _player = &p;
    _armiesTotal = 0;
    _battlesWonTotal = 0;
    _reinforcementTotal = 0;
}

void PlayerView::update(){
    _reinforcementTotal = _player->getReinforcementTotal();
    _armiesTotal = _player->getArmiesTotal();
    _battlesWonTotal = _player->getBattlesWonTotal();

    //Lets print on console just to test the working
    std::cout << "The view was updated for "<< _player->getName() <<" :"<< std::endl;
    std::cout << " - Number of armies is now "<< _armiesTotal << std::endl;
    std::cout << " - Number of reinforcement is now "<< _reinforcementTotal << std::endl;
    std::cout << " - Number of battles won is now "<< _battlesWonTotal << std::endl << std::endl;
}
