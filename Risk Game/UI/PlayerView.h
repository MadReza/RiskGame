#pragma once
#include <iostream>
#include <string>
#include "../Observer.h"
#include "../BattleEngine/Player.h"

class PlayerView : public Observer {
private:
    Player* _player;
    std::set<Country> _countries;
    std::set<Continent> _continents;
    int _reinforcementTotal;
    int _armiesTotal;
    int _battlesWonTotal;
public:
    PlayerView(Player &p);
    void Update();
};
