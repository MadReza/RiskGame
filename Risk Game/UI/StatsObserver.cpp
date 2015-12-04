#include "StatsObserver.h"

StatsObserver::StatsObserver(vector<Player*> p, int mapcountrycount)
{
	countrycount = mapcountrycount;
	for (int i = 0; i != p.size(); i++)
	{
		Stats_Vector.push_back(p[i]);
		p[i]->attach(this);
	}
}

void StatsObserver::display()
{
	COORD gameDisplayCoord = risk::getCursorPosition();
	risk::clsObserver();
	//TODO: DONT CHANGE SIZE OR THIS BORDER WILL PRINT ON THE NEXT LINE AND BREAK FROMATTING
	//WARNING
	cout << "=======================================================================================================================================================================================================" << endl;
	cout << "Player:        ";
	for (int i = 0; i != Stats_Vector.size(); i++)
	{
		if (Stats_Vector[i]->getAlive())
		{
			cout << setfill(' ') << setw(20) << Stats_Vector[i]->getName();
		}
	}

	cout << endl;

	cout << "Player Type:   ";
	for (int i = 0; i != Stats_Vector.size(); i++)
	{
		if (Stats_Vector[i]->getAlive())
		{
			cout << setfill(' ') << setw(20) << Player::playerTypes[Stats_Vector[i]->getType()];
		}
	}
	cout << endl;

	cout << "Battles Won:   ";
	for (int i = 0; i != Stats_Vector.size(); i++)
	{
		if(Stats_Vector[i]->getAlive())
		{
			cout << setfill(' ') << setw(20) << Stats_Vector[i]->getBattlesWonTotal();
		}
	}
	cout << endl;

	cout << "Cards in Hand: ";
	for (int i = 0; i != Stats_Vector.size(); i++)
	{
		if (Stats_Vector[i]->getAlive())
		{
			cout << setfill(' ') << setw(20) << Stats_Vector[i]->getCards()->size();
		}
	}

	cout << endl;

	cout << "Map Occupied:  ";
	for (int i = 0; i != Stats_Vector.size(); i++)
	{
		if (Stats_Vector[i]->getAlive())
		{
			double percent = ((double)Stats_Vector[i]->getCountries().size() / countrycount) * 100;
			
			std::ostringstream strs;
			strs << percent;
			std::string percentage = strs.str();
			percentage += "%";
			cout << setfill(' ') << setw(20) << percentage;
		}
	}

	cout << endl;
	cout << "=======================================================================================================================================================================================================" << endl;
	risk::setCursorPosition(gameDisplayCoord);
}