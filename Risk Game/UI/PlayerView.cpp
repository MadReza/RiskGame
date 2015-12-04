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

	_log = new LogFile();
	_logPhase = nullptr;
	_logAllPhase = true;
}

PlayerView::~PlayerView()
{
	_player->detach(this);
}

void PlayerView::update(){
	_reinforcementTotal = 0;	//TODO @CHRIS @REZA reinforcement call in player was  ouputting shit.
	_continentReinforcements = _player->getContinentReinforcements();
	_countryReinforcements = _player->getCountryReinforcements();
	_armiesTotal = _player->getArmiesTotal();
	_battlesWonTotal = _player->getBattlesWonTotal();


	//Called by a decorator
	if (!startedScreenOutput && risk::obsDisplaying)
	{
		//Lets print on console just to test the working
		std::cout << "The view was updated for " << _player->getName() << " :" << std::endl;
		std::cout << " - Total Number of armies is now " << _armiesTotal << std::endl;
		std::cout << " - Total Number of Continent reinforcement is now " << _continentReinforcements << std::endl;
		std::cout << " - Total Number of Country reinforcement is now " << _countryReinforcements << std::endl;
		std::cout << " - Total Number of reinforcement is now " << _reinforcementTotal << std::endl;
		std::cout << " - Total Number of battles won is now " << _battlesWonTotal << std::endl << std::endl;
		return;
	} 

	//Print to Logger
	if (_log == nullptr)	//If there is no logger then ignore and move on
		return;

	if (_logAllPhase == true)
	{
		switch (_player->currentPhase)
		{
		case Reinforce:
			updateReinforcement();
			break;
		case Attack:
			updateAttack();
			break;
		case Fortification:
			updateFortification();
			break;
		default:
			break;
		}
	}
	else if (_logPhase != nullptr)
	{
		switch (*_logPhase)
		{
		case Reinforce:
			if (_player->currentPhase != Reinforce)
				break;
			updateReinforcement();
			break;
		case Attack:
			if (_player->currentPhase != Attack)
				break;
			updateAttack();
			break;
		case Fortification:
			if (_player->currentPhase != Fortification)
				break;
			updateFortification();
			break;
		default:
			break;
		}
	}
}

void PlayerView::logAllPhase(bool trueFalse)
{
	_logAllPhase = trueFalse;

	if (_logAllPhase)
	{
		delete _logPhase;
		_logPhase = nullptr;
	}
}

void PlayerView::logOnlyPhase(Phase* phase)
{
	if (_logPhase != nullptr)
		delete _logPhase;
	_logPhase = phase;

	if (_logPhase != nullptr)
	{
		_logAllPhase = false;
	}
}

void PlayerView::updateReinforcement()
{
	_log->output("");
	_log->output("***Reinforcement Changed***");
	_log->output("The view was updated for " + _player->getName() + ":");
	_log->output(" - Number of reinforcment is now " + _reinforcementTotal);
	_log->output("***End of Reinforcement Phase Change****");
	_log->output("");
}

void PlayerView::updateAttack()
{
	_log->output("");
	_log->output("***Attack/Battle Changed***");
	_log->output("The view was updated for " + _player->getName() + ":");
	_log->output(" - Number of battles won is now " + _battlesWonTotal);
	_log->output("***End of Battle Phase Change****");
	_log->output("");
}

void PlayerView::updateFortification()
{
	_log->output("");
	_log->output("***Fortification Changed***");
	_log->output("The view was updated for " + _player->getName() + ":");
	_log->output(" - Stub to show player moved armies from here to there");
	_log->output("***End of Fortification Phase Change****");
	_log->output("");
}

void PlayerView::changeLogger(Logger* log)	//Cannot be nullptr
{
	if (log == nullptr)
		return;

	delete _log;
	_log = log;
}