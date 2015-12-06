#pragma once
#include <iostream>
#include <string>
#include <set>
#include "../Observer.h"
#include "../BattleEngine/Player.h"
#include "../Screen.h"
#include "../Logger/Logger.h"
#include "../Logger/LogFile.h"
#include "../Phase.h"

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

	//What to log for each player !
	Logger* _log = nullptr;
	Phase* _logPhase = nullptr;		//Only a Specific Phase
	bool _logAllPhase = false;

	void updateReinforcement();
	void updateAttack();
	void updateFortification();
public:
	PlayerView();
	~PlayerView();
    PlayerView(Player &p);

    void update();

	void changeLogger(Logger* log);
	void logAllPhase(bool trueFalse);
	void logOnlyPhase(Phase* phase);
};
