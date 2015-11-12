#include "Player.h"

Player::Player()
{
	Initialize();
}

Player::Player(string name, Type type_Player)
{
	_name = name;
	typeOfPlayer = type_Player;
	Initialize();
}

Player::Player(string name, Type type_Player, Strategy *strat)
{
	_name = name;
	typeOfPlayer = type_Player;
	Astrategy = strat;
	Initialize();
}

Player::~Player()
{
}

void Player::Initialize()
{
    _armiesTotal = 0;
    _battlesWonTotal = 0;
    _reinforcementTotal = 0;
}

Player::Type Player::getType()
{
	return typeOfPlayer;
}

void Player::setName(string name)
{
	_name = name;
}

string Player::getName()
{
	return _name;
}

void Player::setPlayerStrategy(Strategy *strat)
{
	Astrategy = strat;
}

bool Player::isHuman(Player p)
{
	if (p.getType() == Player::Human)
		return true;
	else
		return false;
}

void Player::SetArmiesTotal(int n) {
    _armiesTotal = n;
    Notify();
}
void Player::SetReinforcementTotal(int n) {
    _reinforcementTotal = n;
    Notify();
}
void Player::SetBattlesWonTotal(int n) {
    _battlesWonTotal = n;
    Notify();
}

int Player::GetArmiesTotal() {
    return _armiesTotal;
}

int Player::GetReinforcementTotal() {
    return _reinforcementTotal;
}

int Player::GetBattlesWonTotal() {
    return _battlesWonTotal;
}

bool Player::GetAlive()
{
	return alive;
}
