#pragma once
#include "Observer.h"
#include "BattleEngine\Player.h"
#include <vector>
#include <iostream>
#include <vector>
using namespace std;

class StatsObserver : public Observer
{

	public:
		StatsObserver(vector<Player*> p, int mapcountrycount); //pass players fron Instantiation::getPlayers
		~StatsObserver();
		void addSubject(Player* p);
		void update()
		{
			display();
		}
		void display();

	private:
		vector<Player*> Stats_Vector;
		int countrycount;

	


};