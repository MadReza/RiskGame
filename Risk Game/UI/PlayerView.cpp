#include "PlayerView.h"

PlayerView::PlayerView(Player &p) {
    p.Attach(this);
    _player = &p;
    _armiesTotal = 0;
    _battlesWonTotal = 0;
    _reinforcementTotal = 0;
}

void PlayerView::Update(){
    _reinforcementTotal = _player->GetReinforcementTotal();
    _armiesTotal = _player->GetArmiesTotal();
    _battlesWonTotal = _player->GetBattlesWonTotal();

    //Lets print on console just to test the working
    std::cout << "The view was updated for "<< _player->getName() <<" :"<< std::endl;
    std::cout << " - Number of armies is now "<< _armiesTotal << std::endl;
    std::cout << " - Number of reinforcement is now "<< _reinforcementTotal << std::endl;
    std::cout << " - Number of battles won is now "<< _battlesWonTotal << std::endl << std::endl;
}
