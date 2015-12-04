#pragma once
#include <iostream>
#include <string>
#include <set>
#include "../Observer.h"
#include "../BattleEngine/Player.h"
#include "../Screen.h"

class PlayerView : public Observer {
private:
    Player* _player;
    std::set<Country> _countries;
    std::set<Continent> _continents;
    int _reinforcementTotal;
	int _countryReinforcements;
	int _continentReinforcements;
    int _armiesTotal;
    int _battlesWonTotal;

	bool startedScreenOutput = false;
	COORD gameCursorCoordinates;

public:
	PlayerView();
    PlayerView(Player &p);
    void update();
};
